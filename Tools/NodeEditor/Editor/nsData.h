/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Charlie C.

    Contributor(s): none yet.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
Data types for special nodes & sockets
*/
#ifndef _nsData_h_
#define _nsData_h_

#include "nsCommon.h"
#include "nsMath.h"


// ----------------------------------------------------------------------------
// Abstract data for custom types attached to nodes.
class nsNodeData
{
protected:
    nsNodeDef *m_parent;

public:

    nsNodeData(nsNodeDef *parent) : m_parent(parent) {}
    virtual ~nsNodeData() {}

    virtual nsNodeData* clone(void) {return new nsNodeData(*this);}

    nsNodeDef *getParent(void) const {return m_parent;}
};


// ----------------------------------------------------------------------------
class nsMotionData : public nsNodeData
{
protected:
    int         m_enum;
    int         m_flag;
    int         m_transform;
    NSvec2      m_cx, m_cy, m_cz;
    nsString    m_relObj;
    bool        m_keep;


public:

    nsMotionData(nsNodeDef *parent) 
        :   nsNodeData(parent), m_enum(-1), m_flag(-1), m_transform(-1), m_cx(0,0), m_cy(0,0), m_cz(0,0), m_relObj(""), m_keep(false)
    {
    }


    nsMotionData(const nsMotionData& rhs) 
        :   nsNodeData(rhs.getParent()), 
            m_enum(rhs.m_enum), 
            m_flag(rhs.m_flag), 
            m_cx(rhs.m_cx), 
            m_cy(rhs.m_cy), 
            m_cz(rhs.m_cz), m_relObj(rhs.m_relObj)
    {
    }

    virtual ~nsMotionData() {}

    virtual nsNodeData *clone(void) {return new nsMotionData(*this); }


    NS_INLINE int                   getEnum(void)                           {return m_enum;}
    NS_INLINE int                   getFlag(void)                           {return m_flag;}
    NS_INLINE int                   getTransform(void)                      {return m_transform;}
    NS_INLINE NSvec2                getClampX(void)                         {return m_cx;}
    NS_INLINE NSvec2                getClampY(void)                         {return m_cy;}
    NS_INLINE NSvec2                getClampZ(void)                         {return m_cz;}
    NS_INLINE const nsString        &getRelitaveObject(void)                {return m_relObj;}
    NS_INLINE bool                  getKeep(void)                           {return m_keep;}

    NS_INLINE void                  setEnum(int v)                          {m_enum = v;}
    NS_INLINE void                  setFlag(int v)                          {m_flag = v;}
    NS_INLINE void                  setTransform(int v)                     {m_transform = v;}
    NS_INLINE void                  setClampX(const NSvec2& v)              {m_cx = v;}
    NS_INLINE void                  setClampY(const NSvec2& v)              {m_cy = v;}
    NS_INLINE void                  setClampZ(const NSvec2& v)              {m_cz = v;}
    NS_INLINE void                  setRelitaveObject(const nsString &v)    {m_relObj = v;}
    NS_INLINE void                  setKeep(bool v)                         {m_keep = v;}
};


// ----------------------------------------------------------------------------
class nsObjectSocketData
{
public:

    enum AccessType
    {
        OSD_DEFAULT,
        OSD_GET,
        OSD_SET,
        OSD_POSITION,
        OSD_ORIENTATION,
        OSD_ROTATION, 
        OSD_LIV_VEL,
        OSD_ANG_VEL,
    };

protected:


    AccessType          m_access;
    nsString            m_object;


public:


    nsObjectSocketData(const nsString &v = "") 
        :   m_access(OSD_DEFAULT), m_object(v)
    {
    }

    nsObjectSocketData(const nsObjectSocketData &rhs) 
        :   m_access(rhs.m_access), m_object(rhs.m_object)
    {
    }

    ~nsObjectSocketData() {}


    NS_INLINE const nsString&       getObject(void) const           {return m_object;}
    NS_INLINE const AccessType&     getAccess(void) const           {return m_access;}
    NS_INLINE void                  setObject(const nsString& v)    {m_object = v;}
    NS_INLINE void                  setAccess(const AccessType& v)  {m_access = v;}
};



// ----------------------------------------------------------------------------
NS_INLINE void nsFromString(const nsString& s, nsObjectSocketData &v)
{ 
    v.setObject(s);
}

// ----------------------------------------------------------------------------
NS_INLINE nsString nsToString(const nsObjectSocketData &v)
{ 
    return v.getObject();
}



// ----------------------------------------------------------------------------
// Clamped data type
template <typename T>
class nsTypeClamp
{
public:

    nsTypeClamp() {}

    nsTypeClamp(const T& v, double _min, double _max, bool clamp) 
        :   m_data(v), m_min(_min), m_max(_max), m_clamp(clamp)
    {
    }


    T       m_data;
    double  m_min, m_max;
    bool    m_clamp;

    NS_INLINE bool operator == (const nsTypeClamp<T>& rhs) const
    {
        return m_data == rhs.m_data;
    }
};


typedef nsTypeClamp<NSvec2> NSClampedVec2; 
typedef nsTypeClamp<NSvec3> NSClampedVec3; 
typedef nsTypeClamp<NSvec4> NSClampedVec4; 


#endif//_nsData_h_

