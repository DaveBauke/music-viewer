#include "mycombobox.h"


//create new epmty combo box with title cbox_name
MyComboBox::MyComboBox(const QString &cbox_name, QWidget *parent) : m_parent(parent){
	m_label = new QLabel(cbox_name,m_parent);
	m_cbox = new QComboBox(m_parent);
	m_query = new QSqlQuery();
	m_layout = new QVBoxLayout();

	m_cbox->addItem("");

	m_layout->addWidget(m_label);		//add label, combo box
	m_layout->addWidget(m_cbox);
	m_layout->addStretch();				//and strech at the end so that there won't be space between label and cbox
}

//create new combo box with title cbox_name and populate it from query
MyComboBox::MyComboBox(const QString &cbox_name, const QString &query, QWidget *parent) : m_parent(parent) {
	m_label = new QLabel(cbox_name,m_parent);
	m_cbox = new QComboBox(m_parent);
	m_query = new QSqlQuery(query);

	if (!PopulateComboBox())
		m_cbox->addItem("");

	m_layout = new QVBoxLayout();

	m_layout->addWidget(m_label);		//add label, combo box
	m_layout->addWidget(m_cbox);
	m_layout->addStretch();				//and strech at the end so that there won't be space between label and cbox
}

//create new combo box with title cbox_name and populate it with item_list
MyComboBox::MyComboBox(const QString &cbox_name, const QStringList &item_list, QWidget *parent) : m_parent(parent) {
	m_label = new QLabel(cbox_name,m_parent);
	m_cbox = new QComboBox(m_parent);

	PopulateComboBox(item_list);

	m_layout = new QVBoxLayout();

	m_layout->addWidget(m_label);		//add label, combo box
	m_layout->addWidget(m_cbox);
	m_layout->addStretch();				//and strech at the end so that there won't be space between label and cbox
}

MyComboBox::~MyComboBox() {
	delete m_label;
	delete m_cbox;
	delete m_layout;

	delete m_query;
}

//populates combo box with empty value at index 0 and items from internal query
//returns true if operation succeded
bool MyComboBox::PopulateComboBox() {
	if(!m_query)
		return false;
	m_cbox->clear();

	m_cbox->addItem("");
	while(m_query->next()){
		m_cbox->addItem(m_query->value(0).toString());
	}

	return true;
}

//sets internal query to query and populates combo box with empty value at index 0 and items from internal query
//returns true if operation succeded
bool MyComboBox::PopulateComboBox(const QString &query) {
	if (query == "")
		return false;
	delete m_query;						//delete earlier query

	m_query = new QSqlQuery(query);		//and set new internal query
	return PopulateComboBox();
}

//populates combo box with empty value at index 0 and items from item_list
//returns true if operation succeded
bool MyComboBox::PopulateComboBox(const QStringList &item_list) {
	m_cbox->clear();
	m_cbox->addItem("");
	m_cbox->addItems(item_list);

	return true;
}

//return layout with label and combo box
QLayout *MyComboBox::getLayout() const{
	return m_layout;
}

//return combo box
QComboBox *MyComboBox::getComboBox() const {
	return m_cbox;
}

//return currently selected value as string
QString MyComboBox::itemText() const {
	return m_cbox->itemText(m_cbox->currentIndex());
}

//return currently value at index position as string
QString MyComboBox::itemText(int index) const {
	return m_cbox->itemText(index);
}

//set current index to 0
void MyComboBox::ClearSelection() {
	m_cbox->setCurrentIndex(0);
}
