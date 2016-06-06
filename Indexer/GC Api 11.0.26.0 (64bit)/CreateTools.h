#pragma once
#include <map>
#include <functional>
#include "ToolDeclarations.h"
#include "GibbsTool.h"
#include "MillTools.h"
#include "LatheTools.h"

#pragma pack(push, create_tools_h, 8)

namespace GCTools
{
	GCTOOLS_API int CreateGibbsTool( int tool, gc_teToolTypes eType, const char* custom_name = "", GC_GibbsTool* ptr = NULL );

	//get last used type or use type above the passed in cell
	GCTOOLS_API gc_teToolTypes GetLastUsedToolType(int iCell);
	GCTOOLS_API GC_GibbsTool* GetLastUsedTool(int iCell);
	GCTOOLS_API GC_GibbsTool* GetLastUsedTool();

	GCTOOLS_API GC_GibbsTool* GetTool( int tool );
	GCTOOLS_API GC_MillTool *GetMillTool(GC_GibbsTool *tool);
	GCTOOLS_API const GC_MillTool *GetMillTool(const GC_GibbsTool *tool);
	GCTOOLS_API GC_LatheTool *GetLatheTool(GC_GibbsTool *tool);
	GCTOOLS_API const GC_LatheTool *GetLatheTool(const GC_GibbsTool *tool);
	GCTOOLS_API GC_MillTool* GetMillTool( int tool );
	GCTOOLS_API GC_LatheTool* GetLatheTool( int tool );
	GCTOOLS_API GC_GibbsTool* GetToolFromIndex(int index);
	GCTOOLS_API void SaveToolsToXMLFiles(const char* dir);
}


#pragma pack(pop, create_tools_h)
