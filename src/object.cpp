#include "object.h"
#define OBJECT_TEST	0//1

Cparameter::Cparameter()
{
	this->in=NULL;
	this->out=NULL;
	this->size=0;
}

Cmyfunc::Cmyfunc(string fun_name, MyFunc  func)
{
	this->name = fun_name;
	this->alias = this->name;
	this->p_func = func;
}

int Cmyfunc::isMe(char *identifier)
{
	if (this->name == identifier) return (int)this->name.length();
	if (this->alias == identifier) return (int)this->alias.length();
	return 0;
}

int Cmyfunc::isMe(string * identifier)
{
	if (this->name == *identifier) return (int)this->name.length();
	if (this->alias == *identifier) return (int)this->alias.length();
	return 0;
}

int Cmyfunc::isMe(string identifier)
{
	if (this->name == identifier) return (int)this->name.length();
	if (this->alias == identifier) return (int)this->alias.length();
	return 0;
}

int Cmyfunc::runMe(void *p, bool new_thread)
{
	if (!this->p_func)	return -1;
	if (new_thread == false)
		return this->p_func(p);
	//cout << "Cmyfunc::runMe->thread\n"; //test ok
	std::thread(this->p_func, p).detach();
	return 0;
}

int object_func(void *p)//this ext function for object class
{
	if (!p) return -1;
	char *cp =(char *) p;
	cout << "object_func:"<<cp<<endl;//test
	return 0;
}

int  runcmd(void *cmd)
{
	return system((char *)cmd);
}

long object_id = 0;
Object::Object()
{
	this->id = ++object_id;
	this->status=0;
	this->action=0;
	this->locate = -1;
	this->name = "Object";
	this->alias = this->name;
	this->name += std::to_string(object_id);//change name for nam +=id
	this->add_ex_func("objec_func", object_func);
	this->add_ex_func("runcmd", runcmd);
	this->addMe();
}

Object::~Object()
{
	this->family.clear();
	this->ex_func.clear();
	this->remove_exist_family();
	this->exist_family.clear();
	this->clear_my_memory();//clear my memory
	this->my_mem.clear();
	this->clear_exist();
	this->exist_list.clear();
}

void Object::myName(Object *o)
{
	if(o)
	{
		cout << "name:" << o->name << " alias:"<<o->alias <<" id:"<< o->id << endl;
		return;
	}
	cout << "name:" << this->name << " alias:"<<this->alias <<" id:"<< this->id << endl;
}

void Object::addMe(Object * o)
{
	if (o) {
		this->family.push_back(o);
		o->exist_family.push_back(this);
	}
	else this->family.push_back(this);
}

void Object::removeMe(void * item)
{
	this->family.remove(item);
}

void Object::remove_exist_family()
{
	Object *o;
	while (!this->exist_family.empty())
	{
		o=(Object *)this->exist_family.back();
		o->removeMe(this);
		this->exist_family.pop_back();
	}
}

int Object::isMe(char *identifier)
{
	if (this->name == identifier) return (int)this->name.length();
	if (this->alias == identifier) return (int)this->alias.length();
	return 0;
}

int Object::isMe(string * identifier)
{
	if (this->name ==* identifier) return (int)this->name.length();
	if (this->alias == *identifier) return (int)this->alias.length();
	return 0;
}

int Object::isMe(string identifier)
{
	if (this->name == identifier) return (int)this->name.length();
	if (this->alias == identifier) return (int)this->alias.length();
	return 0;
}

int Object::isMe(int id)
{
	if (this->id == id) return (int)this->name.length();
	return 0;
}

bool Object::add_ex_func(string fun_name, MyFunc func)
{
	Cmyfunc f(fun_name, func);
	this->ex_func.push_back(f);
	return true;
}

void Object::add_memory(Object *m)
{
	this->my_mem.push_back(m);
	m->exist_list.push_back(this);//this Object 
}

void Object::clear_my_memory(Object *m)
{
	if (m)
	{
		m->exist_list.remove(this);
		this->my_mem.remove(m);
		return;
	}

	Object *p;
	while (!this->my_mem.empty())
	{
		p=this->my_mem.back();
		p->exist_list.remove(this);
		this->my_mem.pop_back();
	}
}

void Object::clear_exist()
{
	Object *o;
	while (!this->exist_list.empty())
	{
		o = (Object *)this->exist_list.back();
		o->my_mem.remove(this);
		this->exist_list.pop_back();
	}
}

int Object::my_family()
{
	int count = 0;
	LIST_FAMILY::iterator it;
	Object *op;
	for (it = this->family.begin(); it != this->family.end(); ++it)
	{
		op = (Object *)*it;
		cout << this->name << ":"<<++count <<":"<< op->name << op->i_am_here() << endl;
	}
	cout << this->name << " my_family count : " << count << endl;
	return count;
}

int Object::my_ex_func()
{
	int count = 0;
	LIST_CMYFUNC::iterator it;
	for (it = this->ex_func.begin(); it != this->ex_func.end(); ++it)
	{
		cout <<this->name<<":"<<++count << ":" << it->name << it->p_func << endl;
	}
	cout << this->name << " my_ex_func count : " << count << endl;
	return count;
}

void Object::my_temp()
{
	if (this->temp.length())	cout << this->temp << endl;
}

void Object::my_syntax()
{
	if (this->syntax.length())	cout << this->syntax << endl;
}

int Object::execute(Object *o, string obj_name, string fun_name, void * p, bool new_thread)
{
	return this->execute(o, &obj_name, &fun_name, p, new_thread);
}

int Object::execute(Object *o, string *obj_name, string * fun_name, void * p, bool new_thread)
{
	int ret = -1;
	if (!o) return this->execute();
	if (o->family.empty()) return -1;

	LIST_FAMILY::iterator it;
	Object *op;

	for (it = o->family.begin(); it != o->family.end(); ++it)
	{
		op = (Object *)*it;
		if (obj_name&&obj_name->empty() == false&& op->isMe(obj_name)) {
			if (fun_name&&fun_name->empty() == false) ret = op->execute(fun_name, p, new_thread);
			else ret = op->execute();
		}
		else
		{
			if (fun_name&&fun_name->empty() == false) ret = op->execute(fun_name, p, new_thread);
			else ret = op->execute();
		}
	}
	if (ret == -1 && fun_name&&fun_name->empty() == false) ret = this->execute((char*)"runcmd", (void *)fun_name->c_str(), new_thread); //auto run extern commant
	return ret;
}

int Object::execute(void *p)
{
	return this->func(p);
}

//if new_thread==true  run function on new thread .
int Object::execute(MyFunc func, void * p, bool new_thread) //execute input func 
{
	if (!func) return -1;
	if (new_thread == false) return func(p);

	std::thread(func, p).detach();

	return 0;
}

int Object::execute(string *fun_name, void * p, bool new_thread) //execute this->ex_func 
{
	return this->execute(fun_name->data(), p, new_thread);
}

int Object::execute(char* fun_name, void * p, bool new_thread)
{
	string s = fun_name;
	cout << "int Object::execute->"<<s << endl;//test
	return this->execute(s, p, new_thread);
}

int Object::execute(string fun_name, void * p, bool new_thread) //execute this->ex_func 
{
	int ret=-1;
	if (this->ex_func.empty()) return -1;
	LIST_CMYFUNC::iterator it;

	for (it = this->ex_func.begin(); it != this->ex_func.end(); ++it)
	{
		if (it->isMe(fun_name))
		{
			ret = it->runMe(p, new_thread);
		}
	}
	return ret;
}

int Object::allot(int size,void * *o_addr)
{
	if (size) {
		try {
			*o_addr = new char[size];//
		}
		catch (...)//fail
		{
			cout<< "error:Object::allot size=" << size << endl;
			return 0;
		}
	}

	return size;
}

int Object::allot(int old_size, void ** o_addr, int new_size, bool mem_cpy)
{
	void * n_addr=NULL;
	if (old_size >= new_size) return old_size;
	new_size=this->allot(new_size,(void **)&n_addr);
	if (!n_addr||new_size<=old_size) return old_size;
	if(mem_cpy&&*o_addr) memcpy(n_addr, *o_addr, old_size);
	this->delete_allot(o_addr);//free  old o_addr memory
	*o_addr = n_addr;
	return new_size;
}

void Object::delete_allot(void **addr)
{
	if (addr&&*addr) {
		delete[](char*) (*addr);
		*addr = NULL;
	}
}

long Object::my_id()
{
	return this->id;
}

Object * Object::i_am_here()
{
	return this;
}

Object * Object::who_am_i()
{
	this->myName();
	return this;
}

int Object::are_you_ok()
{
	return this->status; //normal, success, OK ,Pass!  and so on
}

int Object::func(void *p)
{
	cout << this->name << "Object::func\n";
	return 0;
}

int Object::create(void *p)
{
	return -1;
}

#if OBJECT_TEST
int main()
{
	cout << "Object main !\n";
	return 0;
}
#endif
