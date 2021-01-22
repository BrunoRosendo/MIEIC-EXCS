#include "box.h"
#include <sstream>

Object::Object(unsigned i, unsigned w): id(i), weight(w)
{}

unsigned Object::getID() const {
    return id;
}

unsigned Object::getWeight() const {
    return weight;
}

Box::Box(unsigned cap): id(lastId++), capacity(cap), free(cap)
{}

unsigned Box::getID() const {
    return id;
}

unsigned Box::getFree() const {
    return free;
}

void Box::addObject(Object& obj) {
    free -= obj.getWeight();
    objects.push(obj);
}

void Box::resetID(){
    lastId = 1;
}

unsigned Box::getSize() const {
    return objects.size();
}


ostream& operator<<(ostream& os, Object obj) {
    os << "O" << obj.id << ":" << obj.weight;
    return os;
}

unsigned Box::lastId = 1;


// TODO
bool Object::operator<(const Object& o1) const {
	return weight < o1.getWeight();
}

// TODO
bool Box::operator<(const Box& b1) const {
	return getFree() > b1.getFree();
}

// TODO
string Box::printContent() const {
	string res = "Box " + to_string(getID()) + " ";
    if (objects.empty()) res += "empty!\n";
    else{
        res += "[ ";
        StackObj aux = objects;
        while (!aux.empty()){
            Object b = aux.top();
            aux.pop();
            stringstream stream;
            stream << b;
            string obj;
            stream >> obj;
            res += obj + " ";
        }
        res += "]";
    }
    return res;
}

bool Box::hasObject(const Object &obj) const {
    StackObj objs = objects;
    while (!objs.empty()){
        Object o = objs.top();
        objs.pop();
        if (o.getID() == obj.getID()) return true;
    }
    return false;
}

int Box::getNumObjects() const{
    return objects.size();
}