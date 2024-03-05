/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CAccessControlListGroup.h
 *  PURPOSE:     Access control list group definition class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

class CAccessControlListGroup;

#pragma once

#include "../Config.h"
#include <xml/CXMLNode.h>
#include <list>

class CAccessControlListGroupObject
{
public:
    enum EObjectType
    {
        OBJECT_TYPE_USER,
        OBJECT_TYPE_RESOURCE,
    };

public:
    explicit CAccessControlListGroupObject(const char* szName, EObjectType eObjectType) noexcept 
    {
        m_strKey = GenerateKey(szName, eObjectType);
        m_strName = szName;
        m_eObjectType = eObjectType;
    }

    virtual ~CAccessControlListGroupObject() noexcept {};

    static SString GenerateKey(const char* szName, EObjectType eObjectType) noexcept {
        return SString("%s_%d", szName, (std::uint32_t)eObjectType);
    }

    const char*    GetObjectName() const noexcept { return m_strName; };
    EObjectType    GetObjectType() const noexcept { return m_eObjectType; };
    const SString& GetObjectKey() const noexcept { return m_strKey; };

private:
    SString     m_strName;
    EObjectType m_eObjectType;
    SString     m_strKey;
};

class CAccessControlListGroup
{
    using ACLsList = std::list<class CAccessControlList*>;
    using ObjectList = std::list<class CAccessControlListGroupObject*>;
    using ObjectMap = CFastHashMap<SString, class CAccessControlListGroupObject*>;
public:
    CAccessControlListGroup(const char* szGroupName);
    ~CAccessControlListGroup();

    const char* GetGroupName() const noexcept { return m_strGroupName; };

    CAccessControlListGroupObject* AddObject(const char* szObjectName, CAccessControlListGroupObject::EObjectType eObjectType);
    bool                           FindObjectMatch(const char* szObjectName, CAccessControlListGroupObject::EObjectType eObjectType);
    bool                           RemoveObject(const char* szObjectName, CAccessControlListGroupObject::EObjectType eObjectType);

    bool                      AddACL(class CAccessControlList* pACL);
    bool                      IsACLPresent(class CAccessControlList* pACL);
    class CAccessControlList* GetACL(const char* szACLName);
    void                      RemoveACL(class CAccessControlList* pACL);

    ACLsList &GetACL() noexcept { return m_ACLs; }
    const ACLsList& GetACL() const noexcept { return m_ACLs; }

    std::list<class CAccessControlList*>::iterator            IterBeginACL() { return m_ACLs.begin(); };
    std::list<class CAccessControlList*>::iterator            IterEndACL() { return m_ACLs.end(); };
    std::list<class CAccessControlListGroupObject*>::iterator IterBeginObjects() { return m_Objects.begin(); };
    std::list<class CAccessControlListGroupObject*>::iterator IterEndObjects() { return m_Objects.end(); };

    void WriteToXMLNode(CXMLNode* pNode);
    std::uint32_t GetScriptID() const noexcept { return m_uiScriptID; }

private:
    void OnChange();

    SString m_strGroupName;

    ACLsList m_ACLs;

    ObjectList    m_Objects;
    ObjectMap     m_ObjectsById;
    std::uint32_t m_uiScriptID;
};
