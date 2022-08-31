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
			int ec = in -> read();
			if(ec < 0 && ec != Exception::LS_EEOF)
				throw Exception(ec);
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
		int parseFrom(string &text)
		{
			value = stoi(text);
			int ec = check(text);
			return ec;
		}
		void toString(string &text)
		{
			text = to_string(value);
		}
		int check(string &text)
		{
			string checkText;
			toString(checkText);
			if(text != checkText)
				Exception::LS_EFORMAT;
			return Exception::LS_OK;
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
