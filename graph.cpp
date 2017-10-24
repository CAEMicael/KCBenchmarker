#include "graph.h"
#include "ui_graph.h"
#include <QPaintEvent>
#include <QPainter>
#include <QTextStream>


void Graph::addLine(int id, QString name, QColor color)
{
    m_lines[id] = std::vector<std::pair<int,int> >();
    m_names[id] = name;
    m_colors[id] = color;
}

void Graph::addPoint(int id, int x, int y)
{
    m_lines[id].push_back(std::pair<int,int>(x,y));
    update();
}


void Graph::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter p(this);

    int padding = 0;
    p.setPen(QColor(Qt::black));
    p.setBrush(QBrush(Qt::white));

    QRect arearect = rect().adjusted(padding+5,padding+15,-padding-15,-padding-15);
    p.drawRect(rect().adjusted(padding,padding,-padding,-padding));


    std::vector<int> localxmin;
    std::vector<int> localxmax;
    std::vector<int> localymin;
    std::vector<int> localymax;



    for(QMap<int,std::vector<std::pair<int,int>>>::iterator mapiter = m_lines.begin(); mapiter != m_lines.end(); mapiter++)
    {
        int xmin = 0,xmax = 0,ymin = 0,ymax = 0;
        bool first = true;
        for(std::vector<std::pair<int,int>>::iterator pointiter = mapiter->begin(); pointiter != mapiter->end(); pointiter++)
        {
            int x = pointiter->first;
            int y = pointiter->second;
            if (first)
            {
                xmin = x;
                xmax = x;
                ymin = y;
                ymax = y;
                first = false;
            }
            if (xmin > x) xmin = x;
            if (xmax < x) xmax = x;
            if (ymin > y) ymin = y;
            if (ymax < y) ymax = y;
        }
        localxmin.push_back(xmin);
        localxmax.push_back(xmax);
        localymin.push_back(ymin);
        localymax.push_back(ymax);
    }


    if (true && localxmax.size() > 0) //x scale should not individually scale, therefore always true.
    {
        int xmin = localxmin[0];
        int xmax = localxmax[0];
        for(int num = 1; num < (int)localxmax.size(); num++)
        {
            if (xmin > localxmin[num]) xmin = localxmin[num];
            if (xmax < localxmax[num]) xmax = localxmax[num];
        }

        for(int num = 0; num < (int)localxmax.size(); num++)
        {
            localxmin[num] = xmin;
            localxmax[num] = xmax;
        }

    }


    if (m_globalscale && localxmax.size() > 0)
    {
        int ymin = localymin[0];
        int ymax = localymax[0];
        for(int num = 1; num < (int)localxmax.size(); num++)
        {
            if (ymin > localymin[num]) ymin = localymin[num];
            if (ymax < localymax[num]) ymax = localymax[num];
        }

        for(int num = 0; num < (int)localxmax.size(); num++)
        {
            localymin[num] = ymin;
            localymax[num] = ymax;
        }
    }


    if (m_globalscale && localxmax.size() > 0)
    {
        QString msg;
        QTextStream str(&msg);
        str << localymax[0];
        p.drawText(arearect.topLeft(),msg);

        msg.clear();
        str << localymin[0];
        p.drawText(arearect.adjusted(0,0,0,0).bottomLeft(),msg);
    }


    int containerindex = 0;
    for(QMap<int,std::vector<std::pair<int,int>>>::iterator mapiter = m_lines.begin(); mapiter != m_lines.end(); mapiter++, containerindex++)
    {

        int xmin = localxmin[containerindex];
        int ymin = localymin[containerindex];
        double xscale = (arearect.width())/(double)(localxmax[containerindex]-localxmin[containerindex]);
        double yscale = (arearect.height())/(double)(localymax[containerindex]-localymin[containerindex]);


        int id = mapiter.key();
        int lastareax = 0;
        int lastareay = arearect.bottom();
        p.setPen(QPen(QBrush(m_colors[id]),2));
        for(std::vector<std::pair<int,int>>::iterator pointiter = mapiter->begin(); pointiter != mapiter->end(); pointiter++)
        {
            int x = pointiter->first;
            int y = pointiter->second;

            int areax = arearect.left() + (int)(xscale * (double)(x-xmin));
            int areay = arearect.top() + (int)(yscale * (double)(y-ymin));
            areay = arearect.bottom() - areay;

            p.drawLine(lastareax,lastareay,areax,areay);

            lastareax = areax;
            lastareay = areay;

        }
    }



}

void Graph::setGlobalScale(bool gs)
{
    m_globalscale = gs;
    update();
}


Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph),
    m_globalscale(true)
{
    ui->setupUi(this);
}

Graph::~Graph()
{
    delete ui;
}
