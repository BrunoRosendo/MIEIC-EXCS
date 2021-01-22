#include "Gallery.h"
#include <ostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

Gallery::Gallery(vector<Paint*> c): catalog(PaintCatalogItem("", "", 0, 0.00)), collection(c) {

}

vector<Paint*> Gallery::getCollection() const {
    return collection;
}

void Gallery::setCollection(vector<Paint*> c) {
    collection = c;
}

priority_queue<ExhibitionItem> Gallery::getPaintsToShow() const {
    return paintsToShow;
}
HashTableAuthorRecord Gallery::getAuthorRecords () const {
    return  authorRecords;
}

void Gallery::addAuthorRecord(AuthorRecord ar) {
    authorRecords.insert(ar);
}

void Gallery::generateCatalog() {
    catalog.makeEmpty();
    for(int i = 0; i < collection.size(); i++) {
        catalog.insert(collection[i]);
    }
}

BST<PaintCatalogItem> Gallery::getCatalog() const {
    return catalog;
}


void Gallery::prepareExhibition() {
    while( !paintsToShow.empty())
        paintsToShow.pop();
    for(int i = 0; i < collection.size(); i++) {
        ExhibitionItem ei(collection[i]);
        paintsToShow.push(ei);
    }
}

//-------------------------------------------------------------------------------

bool sortFunc(Paint* p1, Paint* p2){
    if (p1->getYear() == p2->getYear()){
        if (p1->getAuthor() == p2->getAuthor()){
            return p1->getTitle() < p2->getTitle();
        }
        return p1->getAuthor() < p2->getAuthor();
    }
    return p1->getYear() > p2->getYear();
}

//TODO
vector<Paint*> Gallery::getPaintsBy(string a) const {
    vector<Paint*> tmp;
    BSTItrLevel<PaintCatalogItem> it(catalog);
    while (!it.isAtEnd()){
        Paint* p = it.retrieve().getPaint();
        if (p->getAuthor() == a) tmp.push_back(p);
        it.advance();
    }
    sort(tmp.begin(), tmp.end(), sortFunc);
    return tmp;
}

//TODO
vector<Paint*> Gallery::getPaintsBetween(int y1, int y2) const {
    vector<Paint*> tmp;
    BSTItrLevel<PaintCatalogItem> it(catalog);
    while (!it.isAtEnd()){
        Paint* p = it.retrieve().getPaint();
        if (p->getYear() >= y1 && p->getYear() <= y2) tmp.push_back(p);
        it.advance();
    }
    sort(tmp.begin(), tmp.end(), sortFunc);
    return tmp;
}

//TODO
bool Gallery::updateTitle(Paint* p, string tnew) {
    BSTItrLevel<PaintCatalogItem> it(catalog);
    while (!it.isAtEnd()){
        Paint* paint = it.retrieve().getPaint();
        if (paint->getTitle() == p->getTitle() && paint->getAuthor() == p->getAuthor()){
            paint->setTitle(tnew);
            return true;
        }
        it.advance();
    }
    return false;
}


//TODO
int Gallery::recordAvailablePainters() { //carrega a tabela de dispersao com AuthorRecords
    for (int i = 0; i < collection.size(); ++i){
        string author = collection.at(i)->getAuthor();
        AuthorRecord rec(author);
        HashTableAuthorRecord::iterator it;
        bool create = true;
        for (it = authorRecords.begin(); it != authorRecords.end(); ++it){
            if (it->getAuthor() == author){
                AuthorRecord r = *it;
                r.addAvaliablePaint();
                authorRecords.erase(it);
                authorRecords.insert(r);
                create = false;
                break;
            }
        }
        if (create) authorRecords.insert(rec);
    }
    return authorRecords.size();
}

//TODO
double Gallery::totalSells() const {
    double sum = 0;
    HashTableAuthorRecord::const_iterator it;
    for (it = authorRecords.begin(); it != authorRecords.end(); ++it)
        sum += it->getTotalSells();
    return sum;
}

//TODO
double Gallery::sellPaint(string a, string t) {
    AuthorRecord tmp(a);
    HashTableAuthorRecord::iterator it = authorRecords.find(tmp);
    if (it == authorRecords.end()) return 0;
    AuthorRecord newRec = *it;

    double price = 0;
    bool found = false;
    for (int i = 0; i < collection.size(); ++i){
        if (collection.at(i)->getAuthor() == a && collection.at(i)->getTitle() == t){
            price = collection.at(i)->getPrice();
            collection.erase(collection.begin() + i);
            found = true;
            break;
        }
    }

    if (!found) return 0;

    newRec.recordSell(price);
    authorRecords.erase(it);
    authorRecords.insert(newRec);
    return price;
}

//TODO
vector<Paint*> Gallery::nBestExibition(int n, int maxPerYear) {  //escolhe as N mais caras pinturas, dos anos mais antigos, para realizar uma exposição
    vector<Paint*> tmp;
    int num = 0, numYear = 0;
    priority_queue<ExhibitionItem> aux = paintsToShow;
    priority_queue<ExhibitionItem> newQ;
    int year = aux.top().getYear();
    while (num < n && !aux.empty()){
        ExhibitionItem i = aux.top();
        aux.pop();
        if (i.getYear() == year){
            numYear++;
            if (numYear > maxPerYear) {
                newQ.push(i);
                continue;
            }
        }
        else{
            year = i.getYear();
            numYear = 1;
        }
        num++;
        tmp.push_back(i.getPaint());
    }
    while (!aux.empty()){
        newQ.push(aux.top());
        aux.pop();
    }

    paintsToShow = newQ;
    return tmp;
}

//TODO
int Gallery::itemExibitionOrder(string a, string t) {
    int index = 0;
    priority_queue<ExhibitionItem> tmp = paintsToShow;
    while (tmp.size() > 0){
        index++;
        ExhibitionItem i = tmp.top();
        tmp.pop();
        if (i.getAuthor() == a && i.getTitle() == t) return index;
    }
    return 0;
}

