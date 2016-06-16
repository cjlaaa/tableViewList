//
//  ListNode.cpp
//  tableViewList
//
//  Created by 常久龙 on 16/6/15.
//
//

#include "ListNode.h"
#define SUB_MENU_MOVEMENT (pBg->getContentSize().height*0.5)

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
        this->addChild(tableView,0,kTagTableView);
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
    if(m_gameData[idx].isShowMenu)
    {
        size.height = size.height + SUB_MENU_MOVEMENT;
    }
    else
    {
        size.height = size.height;
    }
    pBg->release();
    return size;
}

CCTableViewCell* TableViewList::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
//    CCLog("tableCellAtIndex index:%d",idx);
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
//    CCLog("tableViewSubBtnCallback,%d",cell->getIdx());
    CCSprite *pBg = (CCLabelTTF*)cell->getChildByTag(kTagCellBg);
    CCSprite* pSubMenuBg = dynamic_cast<CCSprite*>(pBg->getChildByTag(kTagCellSubMenuBg));
    pSubMenuBg->stopAllActions();
    
    if(m_gameData[cell->getIdx()].isShowMenu)
    {
        pSubMenuBg->setVisible(true);
        m_gameData[cell->getIdx()].isShowMenu = false;
        setTableViewOffset(false);
    }
    else
    {
        pSubMenuBg->setVisible(false);
        m_gameData[cell->getIdx()].isShowMenu = true;
        setTableViewOffset(true);
    }
}

void TableViewList::setTableViewOffset(bool bIsShow)
{
    CCTableView* tableView = dynamic_cast<CCTableView*>(getChildByTag(kTagTableView));
    CCSprite* pBg = CCSprite::create("militaryRank_img_cellBack_3.png");
    CCSize size = tableView->getContentOffset();
    tableView->reloadData();
    
    if(bIsShow)
    {
        tableView->setContentOffset(CCSize(size.width,size.height-SUB_MENU_MOVEMENT),false);
    }
    else
    {
        tableView->setContentOffset(CCSize(size.width,size.height+SUB_MENU_MOVEMENT),false);
    }
    pBg->release();
}

void TableViewList::cellReset(CCTableViewCell* cell,int idx)
{
    CCString *string = CCString::createWithFormat("%d", idx);
    CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(kTagCellBg)->getChildByTag(kTagCellLabel);
    label->setString(string->getCString());
    CCLabelTTF *pName = (CCLabelTTF*)cell->getChildByTag(kTagCellBg)->getChildByTag(kTagCellName);
    pName->setString(m_gameData[idx].strName.c_str());
    
    cellExpand(cell,idx);
}

void TableViewList::cellInit(CCTableViewCell* cell,int idx)
{
    CCString *string = CCString::createWithFormat("%d", idx);
    
    CCSprite* pBg = CCSprite::create("militaryRank_img_cellBack_3.png");
    pBg->setPositionX(pBg->getContentSize().width/2);
    pBg->setPositionY(pBg->getContentSize().height/2);
    cell->addChild(pBg,kZOrderBack,kTagCellBg);
    
    CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
    label->setPosition(CCPointZero);
    label->setAnchorPoint(CCPointZero);
    label->setTag(kTagCellLabel);
    pBg->addChild(label);
    
    CCSprite* pHead = CCSprite::create(m_gameData[idx].strTexture.c_str());
    pBg->addChild(pHead);
    pHead->setTag(kTagCellHead);
    CCPoint p = ccp(pHead->getContentSize().width/2 + pHead->getContentSize().width/4, pHead->getContentSize().height/2 + pHead->getContentSize().height/4);
    pHead->setPosition(p);
    
    CCLabelTTF *pName = CCLabelTTF::create(m_gameData[idx].strName.c_str(), "Helvetica", 20.0);
    pName->setPosition(CCPointZero);
    pName->setAnchorPoint(CCPointZero);
    pName->setTag(kTagCellName);
    pBg->addChild(pName);
    pName->setPosition(ccp(pBg->getContentSize().width/2,pBg->getContentSize().height/2));
    
    CCMenuItemImage *pBtn = CCMenuItemImage::create("common_btn_red_1.png","common_btn_red_0.png",this,
                                                    menu_selector(TableViewList::tableViewSubBtnCallback));
    CCMenu* pMenu = CCMenu::create(pBtn, NULL);
    pBtn->setPosition(ccp(pBg->getContentSize().width-pBtn->getContentSize().width/2,pBg->getContentSize().height/2));
    pMenu->setPosition(CCPointZero);
    cell->addChild(pMenu,kZOrderMiddle,kTagCellMenu);
    
    CCSprite* pSubMenuBg = CCSprite::create("commonPanelParts_img_bg_expand_1_03.png");
    pBg->addChild(pSubMenuBg,kZOrderBack-1,kTagCellSubMenuBg);
    pSubMenuBg->setPositionX(pBg->getContentSize().width/2);
    pSubMenuBg->setPositionY(pSubMenuBg->getPositionY()-25);
    
    CCMenuItemImage *pSubBtn = CCMenuItemImage::create("common_btn_red_1.png","common_btn_red_0.png",this,
                                                    menu_selector(TableViewList::tableViewSubMenuBtnCallback));
    CCMenu* pSubMenu = CCMenu::create(pSubBtn, NULL);
    pSubBtn->setPosition(pSubMenuBg->getContentSize().width/2,pSubMenuBg->getContentSize().height/3);
    pSubMenu->setPosition(CCPointZero);
    pSubMenuBg->addChild(pSubMenu,kZOrderMiddle,kTagCellSubMenu);
    
    cell->setTag(idx);
    
    cellExpand(cell,idx);
}

void TableViewList::tableViewSubMenuBtnCallback(CCObject* pSender)
{
    CCTableViewCell *cell = (CCTableViewCell*)(((CCMenuItemImage*)pSender)->getParent()->getParent())->getParent()->getParent();
    CCLog("tableViewSubMenuBtnCallback,%d",cell->getIdx());
}

void TableViewList::cellExpand(CCTableViewCell* cell,int idx)
{
    CCSprite* pBg = dynamic_cast<CCSprite*>(cell->getChildByTag(kTagCellBg));
    CCMenu* pBtn = dynamic_cast<CCMenu*>(cell->getChildByTag(kTagCellMenu));
    CCSprite* pSubMenuBg = dynamic_cast<CCSprite*>(pBg->getChildByTag(kTagCellSubMenuBg));
    
    if(m_gameData[idx].isShowMenu)
    {
        pBg->setPositionY(pBg->getContentSize().height/2+SUB_MENU_MOVEMENT);
        if(pBtn!=NULL)pBtn->setPositionY(SUB_MENU_MOVEMENT);
        pSubMenuBg->setVisible(true);
    }
    else
    {
        pBg->setPosition(ccp(pBg->getContentSize().width/2, pBg->getContentSize().height/2));
        if(pBtn!=NULL)pBtn->setPositionY(0);
        pSubMenuBg->setVisible(false);
    }
}

unsigned int TableViewList::numberOfCellsInTableView(CCTableView *table)
{
//    CCLog("g_gameData size %lu",g_gameData.size());
    return m_gameData.size();
}