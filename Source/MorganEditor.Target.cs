// Copyrights P.K.

using UnrealBuildTool;
using System.Collections.Generic;

public class MorganEditorTarget : TargetRules
{
	public MorganEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Morgan" } );
	}
}
