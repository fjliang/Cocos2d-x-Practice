#pragma once
#include"cocos2d.h"
#include<cocos-ext.h>
USING_NS_CC;
USING_NS_CC_EXT;
class TableView1 :public Layer,TableViewDataSource,TableViewDelegate
{
public:
	TableView1();
	~TableView1();
	CREATE_FUNC(TableView1);

	virtual Size cellSizeForTable(TableView *table) {
		return Size(400, 50);
	};

	/**
	* Delegate to respond touch event
	*
	* @param table table contains the given cell
	* @param cell  cell that is touched
	* @js NA
	* @lua NA
	*/
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);

	/**
	* a cell instance at a given index
	*
	* @param idx index to search for a cell
	* @return cell found at idx
	*/
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	/**
	* Returns number of cells in a given table view.
	*
	* @return number of cells
	*/
	virtual ssize_t numberOfCellsInTableView(TableView *table);

	virtual bool init();
};

