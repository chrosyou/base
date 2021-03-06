
#pragma once
#include "baseoperator.h"

class CBaseOpreator : public BaseOpreator
{
public:
	virtual void AddRef();
	virtual void Release();

	virtual int Add(int a, int b);

	/**
    @brief: 移动鼠标到制定位置
	@param[in]: 鼠标移动的位置
	@param[out]：成功为0，失败为非0
    **/
	virtual long MouseMove(POINT point);
	/**
    @brief: 鼠标点击
	@param[in]: 点击的位置, "L" 表示左击， "M" 表示中间， "R" 表示右击
	@param[in]: 点击的次数
	@param[out]：成功为0，失败为非0
    **/
	virtual long MouseClick(LPCTSTR lpType, int iTimes);
	/**
    @brief: 获得鼠标位置
	@param[out]：成功为0，失败为非0
	@param[out]：x
	@param[out]：point是鼠标位置
	**/
	virtual long GetMousePos(POINT& point);
	/**
    @brief: 按键按下
	@param[in]: msdn中指定的按键值(参见Virtual-Key Codes)
	@param[out]：成功为0，失败为非0
    **/
	virtual long KeyboardDown(int iType);
	/**
    @brief: 按键弹起
	@param[in]: msdn中指定的按键值(参见Virtual-Key Codes)
	@param[out]：成功为0，失败为非0
    **/
	virtual long KeyboardUp(int iTypet);
	/**
    @brief: 通过classname将某个窗口激活
	@param[in]: classname(为空时传 L"")
	@param[in]: titlename(为空时传 L"")
	@param[out]：成功为0，失败为非0
    **/
	virtual long SetWindowFocus(LPCTSTR lpClassName, LPCTSTR lpTitleName);
	/**
    @brief: 通过classname将某个窗口显示出来
	@param[in]: classname(为空时传 L"")
	@param[in]: titlename(为空时传 L"")
	@param[in]: 显示类型(SW_SHOWNORMAL 1正常显示, 2最小化，3最大化)
	@param[out]：成功为0，失败为非0
    **/
	virtual long ShowWindows(LPCTSTR lpClassName, LPCTSTR lpTitleName, int iType);
	/**
    @brief: 通过窗口类获得程序坐标
	@param[in]: classname(为空时传 L"")
	@param[in]: titlename(为空时传 L"")
	@param[out]：RECT表示窗口的位置
	**/
	virtual long GetWindowPos(LPCTSTR lpClassName, LPCTSTR lpTitleName, RECT& rect);
	/**
    @brief: 判断窗口是否存在
	@param[in]: classname(为空时传 L"")
	@param[in]: titlename(为空时传 L"")
	@param[out]：0表示存在，其他表示不存在
    **/
	virtual long IsWindowExit(LPCTSTR lpClassName, LPCTSTR lpTitleName);
	/**
    @brief: 取屏幕某点的颜色
	@param[in]: point表示屏幕位置
	@param[out]：成功为0，失败为非0
	@param[out]：r(颜色RGB的值)
	@param[out]：g
	@param[out]：b
    **/
	virtual long GetPiexlColor(POINT pos, int& r, int& g, int& b);

};
