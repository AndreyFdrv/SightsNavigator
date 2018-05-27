#include "MultigraphException.h"
#include <QString>
#include <sstream>
using namespace multigraph;
Exception::Exception():exception()
{

}
Exception::Exception(QString text, int line, QString function, QString timestamp):exception(), Type(MultigraphException),
    Text(text), Line(line), Function(function), Time(timestamp)
{

}
const char *Exception::what() const throw()
{
    std::ostringstream oss;
    oss << "Возникла исключительная ситуация ";
    switch(Type)
    {
    case(MultigraphException):
        oss << "multigraph::Exception\n";
        break;
    case(MultigraphVertexExistingException):
        oss << "multigraph::VertexExistingException\n";
        break;
    case(MultigraphIncorrectIndexException):
        oss << "multigraph::IncorrectIndexException\n";
        break;
    }
    oss << "\"" << Text.toStdString()  << "\" в функции \"" << Function.toStdString() << "\" в строке " << Line
        << ". Время: " << Time.toStdString();
    FullString = oss.str();
    return FullString.c_str();
}
const char *VertexExistingException::what() const throw()
{
    std::ostringstream oss;
    oss << "Возникла исключительная ситуация multigraph::VertexExistingException\n";
    oss << "\"" << Text.toStdString()  << "\" в функции \"" << Function.toStdString() << "\" в строке " << Line
        << ". Имя вершины: " << Name.toStdString() << ". Время: " << Time.toStdString();
    FullString = oss.str();
    return FullString.c_str();
}
