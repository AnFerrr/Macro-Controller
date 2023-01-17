param (
	[switch]$dev = $false,
	[switch]$nopause = $false
)

if ($dev) {
	.\vendor\bin\premake\premake5.exe vs2022 --dev
} else {
	.\vendor\bin\premake\premake5.exe vs2022
}

if (-Not $nopause) {
	PAUSE
}