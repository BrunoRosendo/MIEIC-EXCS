#include "packagingMachine.h"
#include <sstream>
#include <unordered_set>

PackagingMachine::PackagingMachine(int boxCap): boxCapacity(boxCap)
{}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box& b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}


// TODO
unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
	unsigned count = 0;
	vector<Object>::iterator it;
	for (it = objs.begin(); it != objs.end(); ++it){
	    if (it->getWeight() <= boxCapacity){
	        count++;
            objects.push(*it);
	        it = objs.erase(it) - 1;
	    }
	}
	return count;
}

// TODO
Box PackagingMachine::searchBox(Object& obj) {
    vector<Box> removed;
    while (boxes.size() > 0){
        Box b = boxes.top();
        if (b.getFree() >= obj.getWeight()){
            boxes.pop();
            for (int i = 0; i < removed.size(); ++i){
                boxes.push(removed.at(i));
            }
            return b;
        }
        else{
            removed.push_back(b);
            boxes.pop();
        }
    }
    for (int i = 0; i < removed.size(); ++i){
        boxes.push(removed.at(i));
    }

    Box b;
    return b;
}

// TODO
unsigned PackagingMachine::packObjects() {
	unsigned count = 0;
	vector<Object> objectsRemoved;
	unordered_set<unsigned> ids;

	while (!objects.empty()){
	    Object o = objects.top();
	    objectsRemoved.push_back(o);
	    objects.pop();

        Box b = searchBox(o);
        b.addObject(o);
        ids.insert(b.getID());

        vector<Box> removedBoxes;
        bool newBox = true;

        while (!boxes.empty()){
            Box b2 = boxes.top();
            boxes.pop();
            if (b2.getID() == b.getID()){
                boxes.push(b);
                newBox = false;
                break;
            }
            removedBoxes.push_back(b2);
        }
        if (newBox){
            boxes.push(b);
        }
        for (int i = 0; i < removedBoxes.size(); ++i) boxes.push(removedBoxes.at(i));
	}
	for (int i = 0; i < objectsRemoved.size(); ++i){
	    objects.push(objectsRemoved.at(i));
	}
	return ids.size();
}

// TODO
string PackagingMachine::printObjectsNotPacked() const {
	stringstream stream;
	HeapObj objs = objects;
	while (!objs.empty()){
	    Object o = objs.top();
	    objs.pop();
	    bool found = false;

	    HeapBox bs = boxes;
	    while (!bs.empty()){
	        Box b = bs.top();
	        bs.pop();
            if (b.hasObject(o)){
                found = true;
                break;
            }
	    }
	    if (!found) stream << o << "\n";
	}
	stream << "\t";
	string res;
	while (!stream.eof()){
	    string temp;
	    getline(stream, temp, '\t');
	    res += temp;
	}
	if (res == "") res = "No objects!\n";
	return res;
}

// TODO
Box PackagingMachine::boxWithMoreObjects() const {
	if (boxes.empty()) throw MachineWithoutBoxes();

	Box mostObjects;
	int max = 0;
	HeapBox aux = boxes;

	while (!aux.empty()){
	    Box b = aux.top();
	    aux.pop();
	    if (b.getNumObjects() > max){
	        mostObjects = b;
	        max = b.getNumObjects();
	    }
	}
	return mostObjects;
}