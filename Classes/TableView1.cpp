#include "TableView1.h"


TableView1::TableView1()
{
}


TableView1::~TableView1()
{
}
bool TableView1::init(){
	bool bRet = false;
	do{
	CC_BREAK_IF(!Layer::init());
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto tv= TableView::create(this, Size(400, 300));
	tv->setDelegate(this);
	tv->setPosition(visibleSize.width / 2, visibleSize.height/2);
	this->addChild(tv);

	bRet = true;
	} while (0);
	return bRet;
}

TableViewCell* TableView1::tableCellAtIndex(TableView *table, ssize_t idx){

	TableViewCell *cell= table->dequeueCell();
	LabelTTF *label;
	if (cell==NULL){
		cell = TableViewCell::create();
		label = LabelTTF::create();
		label->setTag(100);
		label->setAnchorPoint(Point(0,0));
		cell->addChild(label);
	}

	label = (LabelTTF*)cell->getChildByTag(100);
	label->setString(StringUtils::format("index %dl",idx));

	return cell;

}
ssize_t TableView1::numberOfCellsInTableView(TableView *table){
	return 100;
}
void TableView1 :: tableCellTouched(TableView* table, TableViewCell* cell){
	LabelTTF *label = (LabelTTF *)cell->getChildByTag(100);
	log("%s", label->getString().c_str());
}