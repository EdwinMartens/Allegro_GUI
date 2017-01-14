
class A5Exception: public exception
{
  private:
  string m_strError;

  public:

  A5Exception(string a_strError)
  {
     m_strError = a_strError;
  }

  virtual const char* what() const throw()
  {
    return m_strError.c_str();
  }

  virtual ~A5Exception() throw() { }
};

class GUIException: public A5Exception
{
    public:
    GUIException(string a_strError)
    :A5Exception(a_strError)
    {

    }

};
