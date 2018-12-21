//
//  HRocker.h
//  guyue
//
//  Created by dsh on 15/1/13.
//
//

#ifndef __guyue__HRocker__
#define __guyue__HRocker__

#include "cocos2d.h"

using namespace cocos2d;

//���ڱ�ʶҡ����ҡ�˵ı���
typedef enum{
    tag_rocker,
    tag_rockerBG,
}tagForHRocker;
//���ڱ�ʶҡ�˷���
//typedef enum{
//    FDirUp              = 8,
//    FDirLeftAndUp       = 7,
//    FDirLeft            = 6,
//    FDirDownAndLeft     = 5,
//    FDirDown            = 4,
//    FDirRightAndDown    = 3,
//    FDirRight           = 2,
//    FDirUpAndRight      = 1,
//    FDirNone            = 0
//}tagDirecton;
class HRocker:public Layer
{
public:
    HRocker(void);
    ~HRocker(void);
    //�ص�����
    typedef std::function<void(Point pTD)> JoystickHandler;
    //TouchEnded
    void setJoystickPositionChangeHandler(JoystickHandler);
    //void update(float delta);
    //����ҡ��(ҡ�˵Ĳ�����ͼƬ��Դ����ҡ�˱���ͼƬ��Դ������ʼ����)
    static HRocker* createHRocker(const char *rockerImageName,const char *rockerBGImageName,Point position);
    //����ҡ��(��ʾҡ�ˡ�����ҡ�˴����¼�)
    void startRocker(bool _isStopOther);
    //ֹͣҡ��(����ҡ�ˣ�ȡ��ҡ�˵Ĵ�������)
    //void stopRocker();
    //�жϿ��Ƹ˷��������жϾ����ϡ��¡������˶�
    int rocketDirection;
    //��ǰ�������߷���,�����жϾ���ĳ��򣬾��������һ��ǳ���
    //bool rocketRun;
    CREATE_FUNC(HRocker);
private:
    JoystickHandler _handler;
    //EventListenerTouchOneByOne* _touchEventListener;
    //�Զ����ʼ������
    void rockerInit(const char* rockerImageName,const char* rockerBGImageName,Point position);
    //�Ƿ�ɲ���ҡ��
    bool isCanMove;
    //��ȡ��ǰҡ�����û�������ĽǶ�
    float getRad(Point pos1,Point pos2);
    //ҡ�˱���������
    Point rockerBGPosition;
    //ҡ�˱����İ뾶
    float rockerBGR;
    Point m_sDirection;
    // ��ǰ�����µķ�������һ��ʸ����(-1.0, -1.0)�����·���(1.0, 1.0)�����Ϸ���
    //�����¼�
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    void updateDirectionForTouchLocation(Point location);
    
};


#endif /* defined(__guyue__HRocker__) */
