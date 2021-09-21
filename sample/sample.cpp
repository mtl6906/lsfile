#include "ls/file/API.h"
#include "ls/Exception.h"
#include "ls/io/Factory.h"
#include "iostream"
#include "memory"
#include "queue"

using namespace std;
using namespace ls;

io::Factory factory;
using ls::Exception;

class Int
{
	public:
		int &data()
		{
			return value;
		}
		friend io::InputStream *operator>>(io::InputStream *in, Int &i)
		{
			string text;
			try
			{
				in -> read();
			}
			catch(Exception &e)
			{
				if(e.getCode() != Exception::LS_EEOF)
					throw e;
			}
			text = in -> split();
			i.parseFrom(text);
			return in;
		}
		friend io::OutputStream *operator<<(io::OutputStream *out, Int &i)
		{
			string text;
			i.toString(text);
			out -> append(text);
			out -> write();
			return out;
		}
	protected:
		void parseFrom(string &text)
		{
			value = stoi(text);
			if(check(text) == false)
				throw Exception::LS_EFORMAT;
		}
		void toString(string &text)
		{
			text = to_string(value);
		}
		int check(string &text)
		{
			string checkText;
			toString(checkText);
			return text == checkText;
		}
		int value;
};

void testWrite()
{
	unique_ptr<file::File> file(file::api.get("output"));
	auto out = factory.makeOutputStream(file -> getWriter());
	Int i;
	i.data() = 123456;
	out << i;
}

void testRead()
{
	unique_ptr<file::File> file(file::api.get("output"));
	auto in = factory.makeInputStream(file -> getReader());
	Int i;
	in >> i;
	cout << i.data() << endl;
}

int main()
{
	if(file::api.exist("output") == false)
		file::api.create("output", NORMAL_MODE);
	testWrite();
	testRead();
	return 0;
}
