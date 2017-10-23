#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QMap>

namespace Ui {
class Graph;
}

class Graph : public QWidget
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = 0);
    ~Graph();

    void paintEvent(QPaintEvent *e);

public slots:
    void addLine(int id, QString name, QColor color);
    void addPoint(int id, int x, int y);

    void setGlobalScale(bool gs);

private:
    Ui::Graph *ui;
    QMap<int,QString> m_names;
    QMap<int,QColor> m_colors;
    QMap<int,std::vector<std::pair<int,int> > > m_lines;
    bool m_globalscale;
};

#endif // GRAPH_H
