#include "mycombobox.h"


MyComboBox::MyComboBox(const QString &cbox_name, QWidget *parent) : m_parent(parent){
	m_label = new QLabel(cbox_name,m_parent);
	m_cbox = new QComboBox(m_parent);
	m_query = new QSqlQuery();
	m_layout = new QVBoxLayout();

	m_cbox->addItem("");

	m_layout->addWidget(m_label);
	m_layout->addWidget(m_cbox);
}

MyComboBox::MyComboBox(const QString &cbox_name, const QString &query, QWidget *parent) : m_parent(parent) {
	m_label = new QLabel(cbox_name,m_parent);
	m_cbox = new QComboBox(m_parent);
	m_query = new QSqlQuery(query);

	if (!PopulateComboBox())
		m_cbox->addItem("");

	m_layout = new QVBoxLayout();

	m_layout->addWidget(m_label);
	m_layout->addWidget(m_cbox);
}

MyComboBox::MyComboBox(const QString &cbox_name, const QStringList &item_list, QWidget *parent) : m_parent(parent) {
	m_label = new QLabel(cbox_name,m_parent);
	m_cbox = new QComboBox(m_parent);

	PopulateComboBox(item_list);

	m_layout = new QVBoxLayout();

	m_layout->addWidget(m_label);
	m_layout->addWidget(m_cbox);
}

MyComboBox::~MyComboBox() {
	delete m_label;
	delete m_cbox;
	delete m_layout;

	delete m_query;
}

bool MyComboBox::PopulateComboBox() {
	if(!m_query)
		return false;
	m_cbox->clear();
	//m_query->exec();

	m_cbox->addItem("");
	while(m_query->next()){
		m_cbox->addItem(m_query->value(0).toString());
	}

	return true;
}

bool MyComboBox::PopulateComboBox(const QString &query) {
	if (query == "")
		return false;

	delete m_query;
	m_query = new QSqlQuery(query);
	return PopulateComboBox();
}

bool MyComboBox::PopulateComboBox(const QStringList &item_list) {
	m_cbox->clear();
	m_cbox->addItem("");
	m_cbox->addItems(item_list);

	return true;
}

QLayout *MyComboBox::getLayout() const{
	return m_layout;
}

QComboBox *MyComboBox::getComboBox() const {
	return m_cbox;
}

QString MyComboBox::itemText() const {
	return m_cbox->itemText(m_cbox->currentIndex());
}

QString MyComboBox::itemText(int index) const {
	return m_cbox->itemText(index);
}

void MyComboBox::ClearSelection() {
	m_cbox->setCurrentIndex(0);
}
