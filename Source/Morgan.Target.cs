// Copyrights P.K.

using UnrealBuildTool;
using System.Collections.Generic;

public class MorganTarget : TargetRules
{
	public MorganTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Morgan" } );
	}
}
