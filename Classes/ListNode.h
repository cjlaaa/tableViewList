//
//  ListNode.hpp
//  tableViewList
//
//  Created by 常久龙 on 16/6/15.
//
//

#ifndef ListNode_hpp
#define ListNode_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "cocos-ext.h"
USING_NS_CC_EXT;
using namespace std;


class NodeData
{
public:
    NodeData(string sName)
    {
        strName = sName;
        strTexture = "Icon-114.png";
        nLv = 0;
        isShowMenu = false;
    }
    string strName;
    string strTexture;
    int nLv;
    bool isShowMenu;
};
//static vector<NodeData> g_gameData;

enum
{
    kTagTableView,
    kTagCellBg,
    kTagCellLabel,
    kTagCellHead,
    kTagCellName,
    kTagCellMenu,
    kTagCellSubMenu,
};

enum
{
    kZOrderBack,
    kZOrderMiddle,
    kZOrderFront,
};

class TableViewList : public CCLayer
, public CCTableViewDataSource
, public CCTableViewDelegate
{
public:
    static TableViewList* CreateTableViewList();
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    void tableViewSubBtnCallback(CCObject* pSender);
protected:
    bool Init();
    void cellInit(CCTableViewCell* cell,int nIndex);
    void cellReset(CCTableViewCell* cell,int nIndex);
    void cellExpand(CCTableViewCell* cell,int idx);
    void setTableViewOffset(bool bIsShow);
    vector<NodeData> m_gameData;
};

const std::string g_testNames[] = {
    "衣阿华级",
    "大和级",
    "英王乔治五世级",
    "俾斯麦级",
    "长门级",
    "科罗拉多级",
    "纳尔逊级",
    "北卡罗来纳级",
    "南达科他级",
    "维托里奥级",
    "敦刻尔克级",
    "黎赛留级",
    "宾夕法尼亚级",
    "田纳西级",
    "复仇级",
    "加富尔伯爵级",
    "金刚级",
    "凯撒级",
    "布列塔尼级",
    "新墨西哥级",
    "甘古特级",
    "国王级",
    "玛丽亚皇后级",
    "扶桑级",
    "巴伐利亚级",
    "安德烈亚级",
    "伊势级",
    "内华达级",
    "伊丽莎白女王级",
    "沙恩霍斯特级",
    "阿拉斯加级",
    "声望级",
    "胡德级",
    "塞德利茨级",
    "德意志级",
    "马肯森级",
    "德弗林格尔级",
    "埃塞克斯级",
    "齐柏林伯爵级",
    "大凤级",
    "云龙级",
    "勇敢级",
    "翔鹤级",
    "皇家方舟级",
    "黄蜂级",
    "列克星敦级",
    "光辉级",
    "约克城级",
    "加贺级",
    "赤城级",
    "苍龙级",
    "飞鹰级",
    "独立级",
    "大鹰级",
    "巨人级",
    "天鹰级",
    "祥凤级",
    "卡萨布兰卡级",
    "千岁级",
    "竞技神级",
    "博格级",
    "德梅因级",
    "肯特级",
    "利根级",
    "絮弗伦级",
    "波特兰级",
    "高雄级",
    "阿尔及利亚级",
    "北安普敦级",
    "俄勒冈级",
    "诺福克级",
    "约克级",
    "迪凯斯纳级",
    "特伦托级",
    "博尔扎诺级",
    "妙高级",
    "新奥尔良级",
    "希佩尔海军上将级",
    "伦敦级",
    "扎拉级",
    "彭萨克拉级",
    "巴尔的摩级",
    "最上级",
    "威奇塔级",
    "基洛夫级",
    "青叶级",
    "红色高加索级",
    "古鹰级",
    "快速级",
    "阿贺野级",
    "罗马统帅级",
    "克里夫兰级",
    "卡多纳级",
    "南安普敦级",
    "亚特兰大级",
    "虎级",
    "爱丁堡级",
    "奥斯塔公爵级",
    "大淀级",
    "布鲁克林级",
    "纽伦堡级",
    "黛朵级",
    "蒙特库克利级",
    "莱比锡级",
    "格洛斯特级",
    "斯维尔德洛夫级",
    "林仙级",
    "NULL"
};

#endif /* ListNode_hpp */
