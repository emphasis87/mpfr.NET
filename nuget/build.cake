#addin nuget:?package=Cake.Git

public DirectoryPath GitRoot { get; } = GitFindRootFromPath(MakeAbsolute(Directory(".")));
public FilePath Solution { get; } = Locate("mpfr.NET.sln");
public string Configuration { get; } = "Debug";
public string Version { get; } = "1.0.3";
public string Id { get; } = "System.Numerics.MPFR";

public FilePath Locate(string pattern) => GetFiles(GitRoot + "/**/" + pattern).First();

public MSBuildSettings BuildSettings => new MSBuildSettings {
	Verbosity = Verbosity.Minimal,
	ToolVersion = MSBuildToolVersion.VS2015,
	ArgumentCustomization = args => args
		.Append("/fileLogger")
		.Append("/flp:verbosity=detailed;LogFile=build.log")
		.Append("/clp:verbisity=normal;ErrorsOnly")
		.Append("/maxcpucount"),
};

public string ToMSBuildTaskName(SolutionProject project){
	if (project == null)
		return null;

	var name = project.Name.Replace(".","_").Replace("(","_").Replace(")","_");
	return project.Parent != null ? $"{ToMSBuildTaskName(project.Parent)}\\{name}" : name;
}

public MSBuildSettings AddTargets(MSBuildSettings settings, FilePath solution, string[] projects){
	var projs = projects.Select(x => Locate(x)).ToArray();
	var sln = ParseSolution(solution.FullPath);
	foreach(var project in sln.Projects.Where(x => projs.Any(p => p.FullPath == x.Path.FullPath)))
	{
		var name = ToMSBuildTaskName(project);
		settings.WithTarget($"\"{name}:Rebuild\"");
	}
	return settings;
}

public void Compile(FilePath solution = null, string[] projects = null, MSBuildSettings settings = null) {
	solution = solution ?? Solution;
	projects = projects ?? new [] { $"{Id}.csproj" }; 
	settings = settings ?? BuildSettings;
  
	NuGetRestore(solution.FullPath);
	AddTargets(settings, solution, projects);
	MSBuild(solution.FullPath, settings);
}

Task("Build")
	.Does(() => {
		Compile();
	});
  
Task("Pack")
	.Does(() => {
		CreateDirectory("packages");

		var properties = new Dictionary<string, string>{
			["Id"] = Id,
			["Configuration"] = "Debug",
			["Platform"] = "AnyCPU",
			["Version"] = Version,
		};
		var settings = new NuGetPackSettings {
			Properties = properties,
			OutputDirectory = "packages"
		};
	
		NuGetPack($"{Id}.nuspec", settings);
	
		settings.Symbols = true;
		NuGetPack($"{Id}.symbols.nuspec", settings);
	});

Task("Publish")
	.Does(() => {
		var pkg = Locate($"{Id}.{Version}.nupkg");
		var sympkg = Locate($"{Id}.{Version}.symbols.nupkg");

		Information("Do you want to push packages:");
		Information(pkg.FullPath);
		Information(sympkg.FullPath);
		Console.Write("[yes] [no]: ");
		var result = Console.ReadLine().ToLower().Trim();
		if ("no".StartsWith(result) && result.Length <= 2){
			Information("Skipping push to NuGet.");
			return;
		}
		else if (!"yes".StartsWith(result) || result.Length > 3){
			Information("Unrecognized input. Skipping push to NuGet.");
			return;
		}

		NuGetPush(pkg.FullPath, new NuGetPushSettings());
	});
  
Task("Build+Pack")
	.IsDependentOn("Build")
	.IsDependentOn("Pack");
  
var target = Argument("Target", "Default");
if (target != "Default")
	RunTarget(target);