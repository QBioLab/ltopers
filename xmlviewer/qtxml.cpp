#include <QtCore>
//#include <
    void MainWindow::startTree(){
    	QDomDocument doc("mydocument");
    	QFile file("metadata.xml");
    	if (!file.open(QIODevice::ReadOnly)){
    		cout<< "ERROR"<< endl;
    		return;
    	}
    	if (!doc.setContent(&file)) {
    		cout << "ERROR" << endl;
    		file.close();
    		return;
    	}
    	file.close();
    	QStandardItemModel *model = new QStandardItemModel();
    	preOrder(doc.firstChild(), model);
    	view = new QTreeView(centralWidget);
    	view->setModel(model);
    	view->show();
     
    }
     
    void MainWindow::insertFather(QString name){
    	item = new QStandardItem(name);
    	item->setEditable(false);
    }
     
    void MainWindow::insertChildren(QString name){
    	QStandardItem *subItem = new QStandardItem( name );
    	subItem->setCheckable(true);
    	subItem->setEditable(false);
    	item->appendRow(subItem);
    }
     
    void MainWindow::setItem(QStandardItemModel *model){
    	model->setItem(nRow, item);
    	nRow++;
    }
     
    void MainWindow::preOrder(QDomNode dom, QStandardItemModel *model){
    	if(!dom.isNull()){
    		string aux = dom.nodeName().toStdString();
    		string name = "name";
    		string value = "value";
    		if(dom.isText()){
    			aux = dom.parentNode().nodeName().toStdString();
    			if(strcmp(aux.c_str(),name.c_str())==0){
    				cout << dom.nodeValue().toStdString() << endl;
    				insertFather(dom.nodeValue());
    				setItem(model);
    			}
    			if(strcmp(aux.c_str(),value.c_str())==0){
    				cout << "\t" << dom.nodeValue().toStdString() << endl;
    				insertChildren(dom.nodeValue());
    			}
    		}else{
    			preOrder(dom.firstChild(), model);
    			preOrder(dom.nextSibling(), model);
    		}
     
    	}
    }
