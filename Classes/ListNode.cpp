//
//  ListNode.cpp
//  tableViewList
//
//  Created by 常久龙 on 16/6/15.
//
//

#include "ListNode.h"

TableViewList* TableViewList::CreateTableViewList()
{
    do
    {
        TableViewList* pList = new TableViewList;
        if (pList && pList->Init())
        {
            pList->autorelease();
            return pList;
        }
        delete pList;
    } while (false);
    CCLog("Function TableViewList::CreateTableViewList Error!");
    return NULL;
}

bool TableViewList::Init()
{
    do
    {
        int nIndex = 0;
        while (g_testNames[nIndex]!="NULL")
        {
            m_gameData.push_back(NodeData(g_testNames[nIndex]));
            nIndex++;
        }
//        CCLog("g_gameData size %lu",g_gameData.size());
        
        CCSprite* pBg = CCSprite::create("militaryRank_img_cellBack_3.png");
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCTableView* tableView = CCTableView::create(this,ccp(pBg->getContentSize().width,pBg->getContentSize().height*5));
        tableView->setDirection(kCCScrollViewDirectionVertical);
        tableView->setDelegate(this);
        tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(tableView,0,111);
        tableView->reloadData();
        pBg->release();
        
        return true;
    } while (false);
    CCLog("Function TableViewList::Init Error!");
    return false;
}

void TableViewList::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("tableCellTouched,%d",cell->getIdx());
}

CCSize TableViewList::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    CCSprite* pBg = CCSprite::create("militaryRank_img_cellBack_3.png");
    CCSize size = pBg->getContentSize();
    pBg->release();
    return size;
}

CCTableViewCell* TableViewList::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCLog("tableCellAtIndex index:%d",idx);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        cellInit(cell,idx);
    }
    else
    {
        cellReset(cell, idx);
    }
    return cell;
}

void TableViewList::tableViewSubBtnCallback(CCObject* pSender)
{
    CCTableViewCell *cell = (CCTableViewCell*)(((CCMenuItemImage*)pSender)->getParent()->getParent());
    CCLog("tableViewSubBtnCallback,%d",cell->getIdx());
}

void TableViewList::cellReset(CCTableViewCell* cell,int idx)
{
    CCString *string = CCString::createWithFormat("%d", idx);
    CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(101);
    label->setString(string->getCString());
    CCLabelTTF *pName = (CCLabelTTF*)cell->getChildByTag(103);
    pName->setString(m_gameData[idx].strName.c_str());
}

void TableViewList::cellInit(CCTableViewCell* cell,int idx)
{
    CCString *string = CCString::createWithFormat("%d", idx);
    
    CCSprite* pBg = CCSprite::create("militaryRank_img_cellBack_3.png");
    pBg->setPositionX(pBg->getContentSize().width/2);
    pBg->setPositionY(pBg->getContentSize().height/2);
    cell->addChild(pBg,0,100);
    
    CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
    label->setPosition(CCPointZero);
    label->setAnchorPoint(CCPointZero);
    label->setTag(101);
    cell->addChild(label);
    
    CCSprite* pHead = CCSprite::create(m_gameData[idx].strTexture.c_str());
    cell->addChild(pHead);
    pHead->setTag(102);
    CCPoint p = ccp(pHead->getContentSize().width/2 + pHead->getContentSize().width/4, pHead->getContentSize().height/2 + pHead->getContentSize().height/4);
    pHead->setPosition(p);
    
    CCLabelTTF *pName = CCLabelTTF::create(m_gameData[idx].strName.c_str(), "Helvetica", 20.0);
    pName->setPosition(CCPointZero);
    pName->setAnchorPoint(CCPointZero);
    pName->setTag(103);
    cell->addChild(pName);
    pName->setPosition(ccp(pBg->getContentSize().width/2,pBg->getContentSize().height/2));
    
    CCMenuItemImage *pBtn = CCMenuItemImage::create("common_btn_red_1.png","common_btn_red_0.png",this,
                                                    menu_selector(TableViewList::tableViewSubBtnCallback));
    CCMenu* pMenu = CCMenu::create(pBtn, NULL);
    pBtn->setPosition(ccp(pBg->getContentSize().width-pBtn->getContentSize().width/2,pBg->getContentSize().height/2));
    pMenu->setPosition(CCPointZero);
    cell->addChild(pMenu, 1);
    cell->setTag(idx);
}

unsigned int TableViewList::numberOfCellsInTableView(CCTableView *table)
{
//    CCLog("g_gameData size %lu",g_gameData.size());
    return m_gameData.size();
}