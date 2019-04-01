#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QSqlQuery>

class MyComboBox {
public:
	MyComboBox(const QString &cbox_name, QWidget *parent);
	MyComboBox(const QString &cbox_name, const QString &query, QWidget *parent);
	MyComboBox(const QString &cbox_name, const QStringList &item_list, QWidget *parent);
	virtual ~MyComboBox();

	bool PopulateComboBox();
	bool PopulateComboBox(const QString &query);
	bool PopulateComboBox(const QStringList &list);

	QLayout *getLayout() const;
	QComboBox *getComboBox() const;

	QString itemText() const;
	QString itemText(int index) const;

	void ClearSelection();

private:
	QLabel		*m_label;
	QComboBox	*m_cbox;
	QVBoxLayout *m_layout;
	QSqlQuery	*m_query;

	QWidget		*m_parent;
};

#endif // MYCOMBOBOX_H
