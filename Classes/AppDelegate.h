#pragma once

#include "stdafx.h"

/**
@brief    Cocos2d-x �����̶�� �� �� �ִ� AppDelegate
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    ���ø����̼��� �ʱ�ȭ �� �� ����Ǵ� ����
    @return true    �������� �ʱ�ȭ
    @return false   �ʱ�ȭ�� ���������� �ȵǾ��� �� ��ȯ
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  ���ø����̼� ���� �� ���� �� ��� ����
    @param  ����
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  ���ø����̼� ������ ���� ���� �� ��� ����
    @param  ����
    */
    virtual void applicationWillEnterForeground();
};
