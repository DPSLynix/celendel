#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

int splitImage(QString fileName, QString destFolder, QTextStream& out, int from)
{

    sf::Image im;
    if(!im.LoadFromFile(fileName.toStdString()))
    {
        qDebug() << "Error loading image " << fileName;
        return 0;
    }

    fileName=destFolder + '/' + fileName.mid(fileName.lastIndexOf('/'));

    int sizeX=im.GetWidth(); int sizeY=im.GetHeight();
    int count=0;

    const int block = 32;

    for(int y=0;y<sizeY/block;++y)
    {
        for(int x=0;x<sizeX/block;++x)
        {
            sf::Image tmp;
            tmp.Create(block,block);
            tmp.Copy(im, 0,0, sf::IntRect(x*block, y*block, (x+1)*block, (y+1)*block));
            QString ts=fileName+QString::number(count)+".png";
            tmp.SaveToFile(ts.toStdString());
            out << ts<<"="<<from+count<<'\n';
            qDebug() << "Saving : " << ts;
            ++count;
        }
    }

    return count;
}

int main()
{
    QString folder("C:\\Users\\Gigotdarnaud\\Desktop\\CircleTexturesHD");
    QString outFolder("C:\\Users\\Gigotdarnaud\\Desktop\\CircleTexturesHD\\OUT");

    QDir dir (folder);
    QStringList filters; filters << "*.bmp" << "*.png" << "*.jpg" << "*.tiff";
    QStringList ls=dir.entryList(filters, QDir::Files|QDir::NoDotAndDotDot);

    QFile file(outFolder+'/'+"filelist.list");
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream tstr(&file);

    int c=0;
    for(int i=0, m=ls.size();i<m;++i)
    {
        c+=splitImage(folder+'/'+ls[i], outFolder, tstr,c);
    }

    return 0;
}
