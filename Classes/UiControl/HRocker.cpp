//
//  HRocker.cpp
//  guyue
//
//  Created by dsh on 15/1/13.
//
//

#include "HRocker.h"
const double PI=3.1415;
HRocker::HRocker(void)
{
    //rocketRun=false;
}

HRocker::~HRocker(void)
{
}
void HRocker::setJoystickPositionChangeHandler(JoystickHandler handler)
{
    _handler = handler;
}

//����ҡ��(ҡ�˵Ĳ�����ͼƬ��Դ����ҡ�˱���ͼƬ��Դ������ʼ����)
HRocker* HRocker::createHRocker(const char *rockerImageName,const char *rockerBGImageName,Point position)
{
    HRocker *layer = HRocker::create();
    if (layer)
    {
        layer->rockerInit(rockerImageName,rockerBGImageName,position);
        //layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}

//�Զ����ʼ������
void HRocker::rockerInit(const char* rockerImageName,const char* rockerBGImageName,Point position)
{
    Sprite *spRockerBG = Sprite::create(rockerBGImageName);
    spRockerBG->setPosition(position);
    spRockerBG->setVisible(false);
    addChild(spRockerBG,0,tag_rockerBG);
    
    Sprite *spRocker = Sprite::create(rockerImageName);
    spRocker->setPosition(position);
    spRocker->setVisible(false);
    addChild(spRocker,1,tag_rocker);
    
    rockerBGPosition = position;
    rockerBGR = spRockerBG->getContentSize().width*0.4;//
    rocketDirection=-1;//��ʾҡ�˷��򲻱�
}

//����ҡ��(��ʾҡ�ˡ�����ҡ�˴����¼�)
void HRocker::startRocker(bool _isStopOther)
{
    Sprite *rocker = (Sprite*)this->getChildByTag(tag_rocker);
    rocker->setVisible(true);
    
    Sprite *rockerBG = (Sprite *)this->getChildByTag(tag_rockerBG);
    //rockerBG->setVisible(true);
    rockerBG->setVisible(false);
    
 
    EventListenerTouchOneByOne * _touchEventListener=EventListenerTouchOneByOne::create();
    _touchEventListener->onTouchBegan=CC_CALLBACK_2(HRocker::onTouchBegan, this);
    _touchEventListener->onTouchMoved=CC_CALLBACK_2(HRocker::onTouchMoved, this);
    _touchEventListener->onTouchEnded=CC_CALLBACK_2(HRocker::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchEventListener, this);
    
}

//ֹͣҡ��(����ҡ�ˣ�ȡ��ҡ�˵Ĵ�������)
//void HRocker::stopRocker()
//{
//    CCSprite *rocker = (CCSprite *)this->getChildByTag(tag_rocker);
//    rocker->setVisible(false);
//    
//    CCSprite * rockerBG = (CCSprite *)this->getChildByTag(tag_rockerBG);
//    rockerBG->setVisible(false);
//    //Director::getInstance()->getEventDispatcher()->removeEventListener(this);
//    // CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
//}


//��ȡ��ǰҡ�����û�������ĽǶ�
float HRocker::getRad(Point pos1,Point pos2)
{
    float px1 = pos1.x;
    float py1 = pos1.y;
    float px2 = pos2.x;
    float py2 = pos2.y;
    
    //�õ�����x�ľ���
    float x = px2 - px1;
    //�õ�����y�ľ���
    float y = py1 - py2;
    //���б�߳���
    float xie = sqrt(pow(x,2) + pow(y,2));
    //�õ�����Ƕȵ�����ֵ(ͨ�����Ǻ����еĵ���Ƕ�����ֵ=б��/б��)
    float cosAngle = x / xie;
    //ͨ�������Ҷ����ȡ���ڽǶȵĻ���
    float rad = acos(cosAngle);
    //ע�⣺��������λ��Y����<ҡ�˵�Y���꣬����Ҫȥ��ֵ-0~-180
    if (py2 < py1)
    {
        rad = -rad;
    }
    return rad;
}

Point getAngelePosition(float r,float angle){
    return Point(r*cos(angle),r*sin(angle));
}

//̧���¼�
bool HRocker::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    Point point = pTouch->getLocation();
    Sprite *rocker = (Sprite *)this->getChildByTag(tag_rocker);
    if (rocker->boundingBox().containsPoint(point))
    {
        isCanMove = true;
       // CCLOG("begin true");
    }
    else
    {
       // CCLOG("begin false");
        isCanMove = false;
    }
    return isCanMove;
}
//�ƶ��¼�
void HRocker::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    if (!isCanMove)
    {
        return;
    }
    Point point = pTouch->getLocation();
    Sprite *rocker = (Sprite *)this->getChildByTag(tag_rocker);
    //�õ�ҡ���봥�������γɵĽǶ�
    float angle = getRad(rockerBGPosition,point);
    //�ж�����Բ��Բ�ľ��Ƿ����ҡ�˱����İ뾶
    if (sqrt(pow((rockerBGPosition.x - point.x),2) + pow((rockerBGPosition.y - point.y),2)) >= rockerBGR)
    {
        
        //��֤�ڲ�СԲ�˶��ĳ�������
        rocker->setPosition(getAngelePosition(rockerBGR,angle)+Point(rockerBGPosition.x,rockerBGPosition.y));
        //  CCLOG("touch");
    }
    else
    {
        //��û�г�������ҡ�˸����û��������ƶ�����
        rocker->setPosition(point);
        //CCLOG("touch");
    }
    
    //�жϷ���
    this->updateDirectionForTouchLocation(point);
    
    
    
}
// ���㴥���㵽��������ľ���ֵ��ת���ɽǶȣ��õ���ȷ�ķ���ֵ��Ȼ�󴫵�ֵ��ί��
void HRocker::updateDirectionForTouchLocation(Point location)
{
    /*
    float radians = (location-rockerBGPosition).getAngle();
    float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);
    
    if (degrees <= 22.5 && degrees >= -22.5)
    {
        //right
        m_sDirection = Point(1.0, 0.0);
        rocketDirection=2;
    }
    else if (degrees > 22.5 && degrees < 67.5)
    {
        //bottomright
        m_sDirection = Point(1.0, -1.0);
        rocketDirection=3;
    }
    else if (degrees >= 67.5 && degrees <= 112.5)
    {
        //bottom
        m_sDirection = Point(0.0, -1.0);
        rocketDirection=4;
    }
    else if (degrees > 112.5 && degrees < 157.5)
    {
        //bottomleft
        m_sDirection = Point(-1.0, -1.0);
        rocketDirection=5;
    }
    else if (degrees >= 157.5 || degrees <= -157.5)
    {
        //left
        m_sDirection = Point(-1.0, 0.0);
        rocketDirection=6;
    }
    else if (degrees < -22.5 && degrees > -67.5)
    {
        //topright
        m_sDirection = Point(1.0, 1.0);
        rocketDirection=1;
    }
    else if (degrees <= -67.5 && degrees >= -112.5)
    {
        //top
        m_sDirection = Point(0.0, 1.0);
        rocketDirection=8;
    }
    else if (degrees < -112.5 && degrees > -157.5)
    {
        //topleft
        m_sDirection = Point(-1.0, 1.0);
        rocketDirection=7;
    }
     */
    m_sDirection = ccpSub(location,this->getPosition());
    Point t_direction = m_sDirection.getNormalized();
    
    if (_handler)
        _handler(m_sDirection);
    

}


//�뿪�¼�
void HRocker::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    if (!isCanMove)
    {
        return;
    }
    Sprite *rockerBG = (Sprite*)this->getChildByTag(tag_rockerBG);
    Sprite *rocker = (Sprite*)this->getChildByTag(tag_rocker);
    rocker->stopAllActions();
    rocker->runAction(CCMoveTo::create(0.08f,rockerBG->getPosition()));
    isCanMove = false;
    m_sDirection = Vec2::ZERO;
    //rocketDirection=0;
    //CCLOG("%d",rocketDirection);
    //CCLOG("end");
}
//void HRocker::update(float dt)
//{
//    //�ж��Ƿ���ҡ�˼�������
//    //    switch(rocker->rocketDirection)
//    //    {
//    //        case 1:
//    //            hero->SetAnimation("run_animation.plist","run_animation.png","run_",8,rocker->rocketRun);//"run_"Ϊrun_animation.png����ͼƬ��ÿ��ͼƬ�Ĺ������Ʋ���
//    //            hero->setPosition(ccp(hero->getPosition().x+1,hero->getPosition().y)); //������
//    //            break;
//    //        case  2:
//    //            hero->SetAnimation("run_animation.plist","run_animation.png","run_",8,rocker->rocketRun);//"run_"Ϊrun_animation.png����ͼƬ��ÿ��ͼƬ�Ĺ������Ʋ���
//    //            hero->setPosition(ccp(hero->getPosition().x, hero->getPosition().y+1));   //������
//    //            break;
//    //        case 3:
//    //            hero->SetAnimation("run_animation.plist","run_animation.png","run_",8,rocker->rocketRun);//"run_"Ϊrun_animation.png����ͼƬ��ÿ��ͼƬ�Ĺ������Ʋ���
//    //            hero->setPosition(ccp(hero->getPosition().x-1,hero->getPosition().y));   //������
//    //            break;
//    //        case 4:
//    //            hero->SetAnimation("run_animation.plist","run_animation.png","run_",8,rocker->rocketRun);//"run_"Ϊrun_animation.png����ͼƬ��ÿ��ͼƬ�Ĺ������Ʋ���
//    //            hero->setPosition(ccp(hero->getPosition().x,hero->getPosition().y-1));   //������
//    //            break;
//    //        default:
//    //            hero->StopAnimation();//ֹͣ���ж������˶�
//    //            break;
//    //            
//    //    }
//}
