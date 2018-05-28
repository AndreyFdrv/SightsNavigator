#ifndef MULTIGRAPHEXCEPTION_H
#define MULTIGRAPHEXCEPTION_H
#include <QString>
#include <exception>
namespace multigraph
{
enum ExceptionType { MultigraphException,
                     MultigraphVertexExistingException,
                     MultigraphIncorrectIndexException,
                     MultigraphAllocatorException
                   };
class Exception : public std::exception
{
public:
    Exception();
    Exception(QString text, int line, QString function, QString time);
    virtual const char* what() const throw();
    ExceptionType GetExceptionType() const { return Type; }
protected:
    ExceptionType Type;
    QString Text;
    int Line;
    QString Function;
    QString Time;
    mutable std::string FullString;
};
class VertexExistingException:public Exception
{
public:
    VertexExistingException(QString text, int line, QString function, QString time,
                            QString name):Exception(text, line, function, time), Name(name)
    {
        Type = MultigraphVertexExistingException;
    }
    virtual const char* what() const throw();
    QString Name;
};
class IncorrectIndexException:public Exception
{
public:
    IncorrectIndexException(QString text, int line, QString function, QString time):Exception(text, line, function, time)
    {
        Type = MultigraphIncorrectIndexException;
    }
};
class AllocatorException:public Exception
{
public:
    AllocatorException(QString text, int line, QString function, QString time):Exception(text, line, function, time)
    {
        Type = MultigraphAllocatorException;
    }
};
}
#endif // MULTIGRAPHEXCEPTION_H
