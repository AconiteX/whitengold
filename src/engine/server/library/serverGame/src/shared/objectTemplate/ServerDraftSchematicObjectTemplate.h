//========================================================================
//
// ServerDraftSchematicObjectTemplate.h
//
//IMPORTANT: Any code between //@BEGIN TFD... and //@END TFD... will be
//overwritten the next time the template definition is compiled. Do not
//make changes to code inside these blocks.
//
// copyright 2001 Sony Online Entertainment
//
//========================================================================

#ifndef _INCLUDED_ServerDraftSchematicObjectTemplate_H
#define _INCLUDED_ServerDraftSchematicObjectTemplate_H

#include "ServerIntangibleObjectTemplate.h"
#include "sharedFoundation/DynamicVariable.h"
#include "sharedUtility/TemplateParameter.h"


class Vector;
typedef StructParam<ObjectTemplate> StructParamOT;
//@BEGIN TFD TEMPLATE REFS
class ServerFactoryObjectTemplate;
class ServerObjectTemplate;
//@END TFD TEMPLATE REFS


class ServerDraftSchematicObjectTemplate : public ServerIntangibleObjectTemplate
{
public:
//@BEGIN TFD ID
	enum
	{
		ServerDraftSchematicObjectTemplate_tag = TAG(D,S,C,O)
	};
//@END TFD ID
public:
	         ServerDraftSchematicObjectTemplate(const std::string & filename);
	virtual ~ServerDraftSchematicObjectTemplate();

	virtual Tag getId(void) const;
	virtual Tag getTemplateVersion(void) const;
	virtual Tag getHighestTemplateVersion(void) const;
	static void install(bool allowDefaultTemplateParams = true);

//@BEGIN TFD
public:
	struct IngredientSlot
	{
		bool                   optional;
		StringId               name;
		stdvector<Ingredient>::fwd options;
		std::string            optionalSkillCommand;
		float                  complexity;
		std::string            appearance;
	};

protected:
	class _IngredientSlot : public ObjectTemplate
	{
		friend class ServerDraftSchematicObjectTemplate;
	public:
		enum
		{
			_IngredientSlot_tag = TAG(D,I,N,S)
		};

	public:
		         _IngredientSlot(const std::string & filename);
		virtual ~_IngredientSlot();

	virtual Tag getId(void) const;

public:
	bool                   getOptional(bool versionOk, bool testData = false) const;
	const StringId         getName(bool versionOk, bool testData = false) const;
	void              getOptions(Ingredient &data, int index, bool versionOk) const;
	void              getOptionsMin(Ingredient &data, int index, bool versionOk) const;
	void              getOptionsMax(Ingredient &data, int index, bool versionOk) const;
	size_t            getOptionsCount(void) const;
	const std::string &    getOptionalSkillCommand(bool versionOk, bool testData = false) const;
	float                  getComplexity(bool versionOk, bool testData = false) const;
	float                  getComplexityMin(bool versionOk, bool testData = false) const;
	float                  getComplexityMax(bool versionOk, bool testData = false) const;
	const std::string &    getAppearance(bool versionOk, bool testData = false) const;

#ifdef _DEBUG
public:
	// special code used by datalint
	virtual void testValues(void) const;
#endif

protected:
	virtual void load(Iff &file);

private:
	BoolParam m_optional;		// is the slot optional
	StringIdParam m_name;		// slot name
	stdvector<StructParamOT *>::fwd m_options;		// possible ingredients that can be used to fill the slot
	bool m_optionsLoaded;
	bool m_optionsAppend;
	StringParam m_optionalSkillCommand;		// skill commands needed to access this slot if it is optional (ignored for required slots)
	FloatParam m_complexity;		// adjustment to complexity by using this slot
	StringParam m_appearance;		// if the slot is a component, the name of the hardpoint associated with the slot; if the slot is a resource, a string used to build an appearance file name
	private:
		static void registerMe(void);
		static ObjectTemplate * create(const std::string & filename);
	private:
		_IngredientSlot(const _IngredientSlot &);
		_IngredientSlot & operator =(const _IngredientSlot &);
	};
	friend class ServerDraftSchematicObjectTemplate::_IngredientSlot;

public:
	CraftingType     getCategory(bool testData = false) const;
	const ServerObjectTemplate * getCraftedObjectTemplate() const;
	const ServerFactoryObjectTemplate * getCrateObjectTemplate() const;
	void              getSlots(IngredientSlot &data, int index) const;
	void              getSlotsMin(IngredientSlot &data, int index) const;
	void              getSlotsMax(IngredientSlot &data, int index) const;
	size_t            getSlotsCount(void) const;
	const std::string &    getSkillCommands(int index) const;
	size_t            getSkillCommandsCount(void) const;
	bool                   getDestroyIngredients(bool testData = false) const;
	const std::string &    getManufactureScripts(int index) const;
	size_t            getManufactureScriptsCount(void) const;
	int                    getItemsPerContainer(bool testData = false) const;
	int                    getItemsPerContainerMin(bool testData = false) const;
	int                    getItemsPerContainerMax(bool testData = false) const;
	float                  getManufactureTime(bool testData = false) const;
	float                  getManufactureTimeMin(bool testData = false) const;
	float                  getManufactureTimeMax(bool testData = false) const;
	float                  getPrototypeTime(bool testData = false) const;
	float                  getPrototypeTimeMin(bool testData = false) const;
	float                  getPrototypeTimeMax(bool testData = false) const;

#ifdef _DEBUG
public:
	// special code used by datalint
	virtual void testValues(void) const;
#endif

protected:
	virtual void load(Iff &file);

private:
	IntegerParam m_category;		// schematic category (food, weapon, etc)
	StringParam m_craftedObjectTemplate;		// what object we create
	StringParam m_crateObjectTemplate;		// the "crate" to use when manufacturing multiple copies of the object
	stdvector<StructParamOT *>::fwd m_slots;		// ingredient slots
	bool m_slotsLoaded;
	bool m_slotsAppend;
	stdvector<StringParam *>::fwd m_skillCommands;		// skill commands needed to access this schematic and required slots
	bool m_skillCommandsLoaded;
	bool m_skillCommandsAppend;
	BoolParam m_destroyIngredients;		// flag that the ingredients used in the design stage should be destroyed
	stdvector<StringParam *>::fwd m_manufactureScripts;		// scripts that will be attached to a manufacturing schematic created from this schematic
	bool m_manufactureScriptsLoaded;
	bool m_manufactureScriptsAppend;
	IntegerParam m_itemsPerContainer;		// when manufacturing, how many items will be put in a container (1 = items not in a container)
	FloatParam m_manufactureTime;		// time to manufacture an item (in secs) per complexity point
	FloatParam m_prototypeTime;		// time to create a prototype (in secs) per complexity point
//@END TFD

public:
	// user functions
	virtual Object * createObject(void) const;

protected:
	// user functions
	virtual void     postLoad();

private:
	Tag  m_templateVersion;	// the template version
	bool m_versionOk;	// flag that the template version loaded is the one we expect
	static bool ms_allowDefaultTemplateParams;	// flag to allow defaut params instead of fataling

	static void registerMe(void);
	static ObjectTemplate * create(const std::string & filename);

	// no copying
	ServerDraftSchematicObjectTemplate(const ServerDraftSchematicObjectTemplate &);
	ServerDraftSchematicObjectTemplate & operator =(const ServerDraftSchematicObjectTemplate &);
};


inline void ServerDraftSchematicObjectTemplate::install(bool allowDefaultTemplateParams)
{
	ms_allowDefaultTemplateParams = allowDefaultTemplateParams;
//@BEGIN TFD INSTALL
	ServerDraftSchematicObjectTemplate::registerMe();
	ServerDraftSchematicObjectTemplate::_IngredientSlot::registerMe();
//@END TFD INSTALL
}


#endif	// _INCLUDED_ServerDraftSchematicObjectTemplate_H
