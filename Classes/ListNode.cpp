//
//  ListNode.cpp
//  tableViewList
//
//  Created by 常久龙 on 16/6/15.
//
//

#include "ListNode.h"

ListNode* ListNode::CreateListNode()
{
    do
    {
        ListNode* pListNode = new ListNode;
        if (pListNode && pListNode->Init())
        {
            pListNode->autorelease();
            return pListNode;
        }
        delete pListNode;
    } while (false);
    CCLog("Function ListNode::CreateListNode Error!");
    return NULL;
}

bool ListNode::Init()
{
    do
    {
        CCSprite* pBg = CCSprite::create("militaryRank_img_cellBack_3.png");
        CC_BREAK_IF(pBg==NULL);
        setContentSize(pBg->getContentSize());
        addChild(pBg);
        
        return true;
    } while (false);
    CCLog("Function ListNode::Init Error!");
    return false;
}

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
            g_gameData.push_back(NodeData(g_testNames[nIndex]));
            nIndex++;
        }
        CCLog("g_gameData size %lu",g_gameData.size());
        
        ListNode* pBg = ListNode::CreateListNode();
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
    ListNode* pBg = ListNode::CreateListNode();
    CCSize size = pBg->getContentSize();
    pBg->release();
    return size;
}

CCTableViewCell* TableViewList::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *string = CCString::createWithFormat("%d", idx);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        ListNode* pBg = ListNode::CreateListNode();
        pBg->setPositionX(pBg->getContentSize().width/2);
        pBg->setPositionY(pBg->getContentSize().height/2);
        cell->addChild(pBg,0,1);
        
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
        label->setPosition(CCPointZero);
        label->setAnchorPoint(CCPointZero);
        label->setTag(101);
        cell->addChild(label);
        
        CCSprite* pHead = CCSprite::create(g_gameData[idx].strTexture.c_str());
        cell->addChild(pHead);
        pHead->setTag(102);
        CCPoint p = ccp(pHead->getContentSize().width/2 + pHead->getContentSize().width/4, pHead->getContentSize().height/2 + pHead->getContentSize().height/4);
        pHead->setPosition(p);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(101);
        label->setString(string->getCString());
//        CCSprite* pHead = dynamic_cast<CCSprite*>(getChildByTag(102));
//        pHead->initWithFile(g_gameData[idx].strTexture.c_str());
    }
    return cell;
}

unsigned int TableViewList::numberOfCellsInTableView(CCTableView *table)
{
    CCLog("g_gameData size %lu",g_gameData.size());
    return g_gameData.size();
}