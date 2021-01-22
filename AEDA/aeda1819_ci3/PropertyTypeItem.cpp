#include "PropertyTypeItem.h"

PropertyTypeItem::PropertyTypeItem(string address, string postalCode, string typology, int maxPrice) {
	this->address = address;
	this->postalCode = postalCode;
	this->typology = typology;
	this->maxPrice = maxPrice;
}

string PropertyTypeItem::getAddress() const {
	return this->address;
}

string PropertyTypeItem::getPostalCode() const {
	return this->postalCode;
}

string PropertyTypeItem::getTypology() const {
	return this->typology;
}

int PropertyTypeItem::getMaxPrice() const {
	return this->maxPrice;
}

vector<Property*> PropertyTypeItem::getItems() const {
	return this->items;
}

void PropertyTypeItem::setItems(vector<Property*> properties) {
	items = properties;
}

void PropertyTypeItem::addItems(Property* property) {
	this->items.push_back(property);
}

//
// TODO
//

bool PropertyTypeItem::operator<(const PropertyTypeItem &pti1) const {
	if (this->address == pti1.getAddress()){
	    if (this->postalCode == pti1.getPostalCode()){
            if (this->typology == pti1.getTypology()){
                return this->maxPrice < pti1.getMaxPrice();
            }
            return this->typology < pti1.getTypology();
	    }
	    return this->postalCode < pti1.getPostalCode();
	}
	return this->address < pti1.getAddress();
}

bool PropertyTypeItem::operator==(const PropertyTypeItem &pti1) const {
    if (this->address == pti1.getAddress()){
        return this->postalCode == pti1.getPostalCode();
    }
    return false;
}
