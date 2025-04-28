import sys, os, time

if len(sys.argv) == 2:
	os.chdir(sys.argv[1])
	print("Python codegen directory: "+sys.argv[1])

settings_raw = open(r"src\Settings.hpp", "r").read()
settings = settings_raw.split("//MCM_START")[1].split("//MCM_END")[0]

sliders = [] # List of pairs [[name, default, format, ranemin, rangemax, step, rel]...]
fsliders = [] # List of pairs [[name, default, format, ranemin, rangemax, step, rel]...]
options = [] # List of pairs [[name, default, rel]...]
colors = [] # List of pairs [[name, default, rel]...]
texts = [] # List of pairs [[name, default, rel]...]
page_data = [] # List of pairs [[pagename, [lines]]]
descriptions = [] # List of pairs [[name, description]...]

def processLine(line, page_lines):
	rel = False
	flag = 0
	if line == "":
		return page_lines
	if "**RELOAD" in line:
		line = line.replace("**RELOAD", "").strip()
		rel = True
	if "?:?" in line:
		line, flag = [x.strip() for x in line.split("?:?")]
	if line.startswith("//"):
		command = line.split(" ")[0].strip()
		if command == "//Header":
			the_rest = " ".join(line.split(" ")[1:]).strip() + " "
			page_lines.append(f'AddHeaderOption("{the_rest}")')
		if command == "//Column":
			page_lines.append('SetCursorPosition(1)')
		if command == "//Empty":
			page_lines.append('AddEmptyOption()')
		if command == "//Flag":
			flag_name, requires = [x.strip() for x in (" ".join(line.split(" ")[1:]).strip()).split("//")]
			req = []
			for r in [x.strip() for x in requires.split(",")]:
				if r.startswith("ESP:"):
					req.append(f'Game.GetModByName("{r.split(":")[1]}") != 255')
				elif r.startswith("VAR:"):
					req.append(f'{r.split(":")[1]}')
				else:
					req.append(r)
			if req is not None:
				page_lines.append(f'int {flag_name} = 1')
				page_lines.append(f'If {" && ".join(req)}')
				page_lines.append(f'\t{flag_name} = 0')
				page_lines.append(f'EndIf')
	elif line.startswith("int "):
		if len(line.split("//")) != 5:
			print(f'Error on line: {line}')
		var, title, desc, form, rang = line.split("//")
		var_name = var.strip().split(" ")[1]
		var_def = var.strip().split(" ")[3][:-1]
		range_min, range_max, step = [x.strip() for x in rang[1:-1].split(",")]
		sliders.append([var_name, var_def, form, range_min, range_max, step, rel])
		descriptions.append([var_name, desc])
		page_lines.append(f'{var_name}OID = AddSliderOption("{title}  ", {var_name}, "{form}", {flag})')
	elif line.startswith("float "):
		if len(line.split("//")) != 5:
			print(f'Error on line: {line}')
		var, title, desc, form, rang = line.split("//")
		var_name = var.strip().split(" ")[1]
		var_def = var.strip().split(" ")[3][:-1]
		if var_def[-1] == "f":
			var_def = var_def[:-1]
		if '.' not in var_def:
			var_def = var_def + '.0'
		range_min, range_max, step = [x.strip() for x in rang[1:-1].split(",")]
		fsliders.append([var_name, var_def, form, range_min, range_max, step, rel])
		descriptions.append([var_name, desc])
		page_lines.append(f'{var_name}OID = AddSliderOption("{title}  ", {var_name}, "{form}", {flag})')
	elif line.startswith("bool "):
		if len(line.split("//")) != 3:
			print(f'Error on line: {line}')
		var, title, desc = line.split("//")
		var_name = var.strip().split(" ")[1]
		var_def = var.strip().split(" ")[3][:-1]
		options.append([var_name, var_def, rel])
		descriptions.append([var_name, desc])
		page_lines.append(f'{var_name}OID = AddToggleOption("{title}  ", {var_name}, {flag})')
	elif line.startswith("color "):
		if len(line.split("//")) != 3:
			print(f'Error on line: {line}')
		var, title, desc = line.split("//")
		var_name = var.strip().split(" ")[1]
		var_def = var.strip().split(" ")[3][:-1]
		colors.append([var_name, var_def, rel])
		descriptions.append([var_name, desc])
		page_lines.append(f'{var_name}OID = AddColorOption("{title}  ", {var_name}, {flag})')
	elif line.startswith("text "):
		if len(line.split("//")) != 3:
			print(f'Error on line: {line}')
		var, title, desc = line.split("//")
		var_name = var.strip().split(" ")[1]
		var_def = var.strip().split(" ")[3][:-1]
		texts.append([var_name, var_def, rel])
		descriptions.append([var_name, desc])
		page_lines.append(f'{var_name}OID = AddInputOption("{title}  ", {var_name}, {flag})')

	return page_lines

pages = settings.split("//Page")[1:]
for page in pages:
	page_name = page.split('\n')[0].strip() + " "
	#print(f"Creating page {page_name}")
	page_lines = []
	for line in [x.strip() for x in page.split('\n')[1:]]:
		page_lines = processLine(line, page_lines)

	page_data.append([page_name, page_lines])

pre_page = settings.split("//Page")[0]
pages_flags = []
for line in [x.strip() for x in pre_page.split('\n')[1:]]:
	pages_flags = processLine(line, pages_flags)


Head = """;THIS SCRIPT IS AUTO GENERATED
Scriptname DCurses_MCM extends SKI_ConfigBase

function UpdateSKSE() global Native
bool function CheckSTNG() global Native
bool function CheckLM() global Native

Perk Property PerkLooted Auto

Event OnGameStarted()
	Debug.trace("DCurses player alias on load game")
	UnregisterForUpdate()
	RegisterForUpdate(1)
	RegisterForModEvent("HookAnimationStart", "OnSexStart")
	RegisterForModEvent("HookAnimationEnd", "OnSexEnd")
EndEvent

Event OnUpdate()
	DCursesLib.OnUpdate()
EndEvent

Event OnSexEnd(int tid, bool HasPlayer)
	If HasPlayer
		SexLabFramework sexlab = Game.GetFormFromFile(0x0d62, "SexLab.esm") as SexLabFramework
		sslThreadController thread = sexlab.GetController(tid)
		Actor[] positions = thread.positions
		DCursesLib.SexEnded(positions)
	EndIf
EndEvent

Event OnSexStart(int tid, bool HasPlayer)
	If HasPlayer
		SexLabFramework sexlab = Game.GetFormFromFile(0x0d62, "SexLab.esm") as SexLabFramework
		sslThreadController thread = sexlab.GetController(tid)
		Actor[] positions = thread.positions
		DCursesLib.SexStarted(positions)
	EndIf
EndEvent

"""

Page = ""

Page += '\n\nEvent OnPageReset(string page)'
Page += ''.join([f'\n\t{x}' for x in pages_flags])
Page += f'\n\tSetCursorFillMode(TOP_TO_BOTTOM)\n\tIf page == "" || page == "{page_data[0][0]}"'
Page += ''.join([f'\n\t\t{x}' for x in page_data[0][1]])
for page in page_data[1:]:
	Page += f'\n\tElseif page == "{page[0]}"'
	Page += ''.join([f'\n\t\t{x}' for x in page[1]])
Page += "\n\tEndIf\nEndEvent"

ConfigInit = ""
ConfigInit += f'\n\nFunction Initialize()\n\tPages = new String[{len(page_data)}]'
for i, page in enumerate(page_data):
	ConfigInit += f'\n\tPages[{i}] = "{page[0]}"'
ConfigInit += "\nEndFunction"

ConfigInit += """

Event OnConfigInit()
	Initialize()
EndEvent

Event OnConfigOpen()
	Initialize()
EndEvent
"""

ConfigClose = """

Event OnConfigClose()
	UpdateSKSE()
EndEvent
"""

Defs = ""

Defs += ''.join([f'\nInt Property {x[0]} = {x[1]} Auto\nInt {x[0]}OID' for x in sliders])
Defs += ''.join([f'\nFloat Property {x[0]} = {x[1]} Auto\nInt {x[0]}OID' for x in fsliders])
Defs += ''.join([f'\nBool Property {x[0]} = {x[1]} Auto\nInt {x[0]}OID' for x in options])
Defs += ''.join([f'\nInt Property {x[0]} = {x[1]} Auto\nInt {x[0]}OID' for x in colors])
Defs += ''.join([f'\nString Property {x[0]} = {x[1]} Auto\nInt {x[0]}OID' for x in texts])

Highlights = ""

Highlights += f"\n\nEvent OnOptionHighlight(int option)"
Highlights += ''.join([f'\n\tIf option == {x[0]}OID\n\t\tSetInfoText("{x[1]}")\n\t\tReturn\n\tEndif' for x in descriptions])
Highlights += "\nEndEvent"

Options = ""
			
parse = lambda x: f'\n\tIf option == {x[0]}OID\n\t\t{x[0]} = !{x[0]}\n\t\tSetToggleOptionValue({x[0]}OID, {x[0]})\n\t\t{"ForcePageReset()\n\t\t" if x[2] else ""}Return\n\tEndif'
Options += '\n\nEvent OnOptionSelect(int option)'
Options += ''.join([parse(x) for x in options])
Options += "\nEndEvent"

SliderOpen = ""

parse = lambda x: f'\n\tIf option == {x[0]}OID\n\t\tSetSliderDialogStartValue({x[0]})\n\t\tSetSliderDialogDefaultValue({x[1]})\n\t\tSetSliderDialogRange({x[3]}, {x[4]})\n\t\tSetSliderDialogInterval({x[5]})\n\t\tReturn\n\tEndif'
SliderOpen += "\n\nEvent OnOptionSliderOpen(int option)"
SliderOpen += ''.join([parse(x) for x in sliders])
SliderOpen += ''.join([parse(x) for x in fsliders])
SliderOpen += "\nEndEvent"

SliderAccept = ""

parse = lambda x: f'\n\tIf option == {x[0]}OID\n\t\t{x[0]} = value as int\n\t\tSetSliderOptionValue(option, value, "{x[2]}"){"\n\t\t"}\n\t\t{"ForcePageReset()\n\t\t" if x[6] else ""}Return\n\tEndif'
parsef = lambda x: f'\n\tIf option == {x[0]}OID\n\t\t{x[0]} = value\n\t\tSetSliderOptionValue(option, value, "{x[2]}")\n\t\t{"ForcePageReset()\n\t\t" if x[6] else ""}Return\n\tEndif'
SliderAccept += """\n\nEvent OnOptionSliderAccept(int option, float value)
"""
SliderAccept += ''.join([parse(x) for x in sliders])
SliderAccept += ''.join([parsef(x) for x in fsliders])
SliderAccept += "\nEndEvent"

InputOpen = ""

parse = lambda x: f'\n\tIf option == {x[0]}OID\n\t\tSetInputDialogStartText({x[0]})\n\t\tReturn\n\tEndif'
InputOpen += "\n\nEvent OnOptionInputOpen(int option)"
InputOpen += ''.join([parse(x) for x in texts])
InputOpen += "\nEndEvent"

InputAccept = ""

parse = lambda x: f'\n\tIf option == {x[0]}OID\n\t\t{x[0]} = value\n\t\tSetInputOptionValue(option, value)\n\t\t{"ForcePageReset()\n\t\t" if x[2] else ""}Return\n\tEndif'
InputAccept += """\n\nEvent OnOptionInputAccept(int option, string value)
"""
InputAccept += ''.join([parse(x) for x in texts])
InputAccept += "\nEndEvent"

ColorOpen = ""

parse = lambda x: f'\n\tIf option == {x[0]}OID\n\t\tSetColorDialogStartColor({x[0]})\n\t\tSetColorDialogDefaultColor({x[1]})\n\t\tReturn\n\tEndif'
ColorOpen += "\n\nEvent OnOptionColorOpen(int option)"
ColorOpen += ''.join([parse(x) for x in colors])
ColorOpen += "\nEndEvent"

ColorAccept = ""
parse = lambda x: f'\n\tIf option == {x[0]}OID\n\t\t{x[0]} = color as int\n\t\tSetColorOptionValue(option, color)\n\t\t{"ForcePageReset()\n\t\t" if x[2] else ""}Return\n\tEndif'
ColorAccept += "\n\nEvent OnOptionColorAccept(int option, int color)"
ColorAccept += ''.join([parse(x) for x in colors])
ColorAccept += "\nEndEvent"

with open("DCurses_MCM.psc", "w") as f:
	f.write(Head)
	f.write(Defs)
	f.write(ConfigInit)
	f.write(ConfigClose)
	#f.write(UpdateSKSE)
	f.write(Page)
	f.write(Highlights)
	f.write(Options)
	f.write(SliderOpen)
	f.write(SliderAccept)
	f.write(InputOpen)
	f.write(InputAccept)
	f.write(ColorOpen)
	f.write(ColorAccept)




# C++ CODEGEN

#UpdateSKSE

index = settings_raw.split("//CODEGEN_START_UPDATE")[0].replace('\r', '').rfind('\n')
indent = settings_raw.split("//CODEGEN_START_UPDATE")[0][index:]
pre = settings_raw.split("//CODEGEN_START_UPDATE")[0] + "//CODEGEN_START_UPDATE"
post = f"{indent}//CODEGEN_END_UPDATE" + settings_raw.split("//CODEGEN_END_UPDATE")[1]

parse = lambda x: f'{indent}settings.{x} = GetMCMSetting("{x}")->GetSInt();'
mid = ''.join(parse(x[0]) for x in sliders)
mid += ''.join(parse(x[0]) for x in colors)

parsef = lambda x: f'{indent}settings.{x} = GetMCMSetting("{x}")->GetFloat();'
mid += ''.join(parsef(x[0]) for x in fsliders)

parseb = lambda x: f'{indent}settings.{x} = GetMCMSetting("{x}")->GetBool();'
mid += ''.join(parseb(x[0]) for x in options)

parse = lambda x: f'{indent}settings.{x} = GetMCMSetting("{x}")->GetString();'
mid += ''.join(parse(x[0]) for x in texts)

settings_raw = pre + mid + post

index = settings_raw.split("//CODEGEN_START_TOJSON")[0].replace('\r', '').rfind('\n')
indent = settings_raw.split("//CODEGEN_START_TOJSON")[0][index:]
pre = settings_raw.split("//CODEGEN_START_TOJSON")[0] + "//CODEGEN_START_TOJSON"
post = f"{indent}//CODEGEN_END_TOJSON" + settings_raw.split("//CODEGEN_END_TOJSON")[1]

parse = lambda x: f'{indent}{{"{x}", settings.{x}}},'
mid = ''.join(parse(x[0]) for x in sliders)
mid += ''.join(parse(x[0]) for x in fsliders)
mid += ''.join(parse(x[0]) for x in options)
mid += ''.join(parse(x[0]) for x in colors)
mid += ''.join(parse(x[0]) for x in texts)

settings_raw = pre + mid + post

index = settings_raw.split("//CODEGEN_START_FROMJSON")[0].replace('\r', '').rfind('\n')
indent = settings_raw.split("//CODEGEN_START_FROMJSON")[0][index:]
pre = settings_raw.split("//CODEGEN_START_FROMJSON")[0] + "//CODEGEN_START_FROMJSON"
post = f"{indent}//CODEGEN_END_FROMJSON" + settings_raw.split("//CODEGEN_END_FROMJSON")[1]

parse = lambda x, y: f'{indent}settings.{x} = static_cast<int>(j.value("{x}", {y}));{indent}SetMCMInt("{x}",settings.{x});'
mid = ''.join(parse(x[0], x[1]) for x in sliders)
mid += ''.join(parse(x[0], x[1]) for x in colors)

parsef = lambda x, y: f'{indent}settings.{x} = static_cast<float>(j.value("{x}", {y}));{indent}SetMCMFloat("{x}",settings.{x});'
mid += ''.join(parsef(x[0], x[1]) for x in fsliders)

parseb = lambda x, y: f'{indent}settings.{x} = static_cast<bool>(j.value("{x}", {y}));{indent}SetMCMBool("{x}",settings.{x});'
mid += ''.join(parseb(x[0], x[1]) for x in options)

parset = lambda x, y: f'{indent}settings.{x} = j.value("{x}", {y});{indent}SetMCMString("{x}",settings.{x});'
mid += ''.join(parset(x[0], x[1]) for x in texts)

settings_raw = pre + mid + post

index = settings_raw.split("//CODEGEN_START_RESET")[0].replace('\r', '').rfind('\n')
indent = settings_raw.split("//CODEGEN_START_RESET")[0][index:]
pre = settings_raw.split("//CODEGEN_START_RESET")[0] + "//CODEGEN_START_RESET"
post = f"{indent}//CODEGEN_END_RESET" + settings_raw.split("//CODEGEN_END_RESET")[1]

parse = lambda x, y: f'{indent}settings.{x} = {y};{indent}SetMCMInt("{x}",settings.{x});'
mid = ''.join(parse(x[0], x[1]) for x in sliders)
mid += ''.join(parse(x[0], x[1]) for x in colors)

parsef = lambda x, y: f'{indent}settings.{x} = {y}f;{indent}SetMCMFloat("{x}",settings.{x});'
mid += ''.join(parsef(x[0], x[1]) for x in fsliders)

parseb = lambda x, y: f'{indent}settings.{x} = {y};{indent}SetMCMBool("{x}",settings.{x});'
mid += ''.join(parseb(x[0], x[1]) for x in options)

parset = lambda x, y: f'{indent}settings.{x} = {y};{indent}SetMCMString("{x}",settings.{x});'
mid += ''.join(parset(x[0], x[1]) for x in texts)

settings_raw = pre + mid + post


with open(r"src\Settings.hpp", "w") as f:
	f.write(settings_raw)


#DeviceListNames

devices_raw = open(r"src\Devices.hpp", "r").read()

device_names = [x.split(" ")[1].strip() for x in devices_raw.split("struct Devices {")[1].split("};")[0].split(";")[1:-1]]

#print(device_names)

index = devices_raw.split("//CODEGEN_START_DEVICES_NAMES")[0].replace('\r', '').rfind('\n')
indent = devices_raw.split("//CODEGEN_START_DEVICES_NAMES")[0][index:]
pre = devices_raw.split("//CODEGEN_START_DEVICES_NAMES")[0] + "//CODEGEN_START_DEVICES_NAMES"
post = f"{indent}//CODEGEN_END_DEVICES_NAMES" + devices_raw.split("//CODEGEN_END_DEVICES_NAMES")[1]

parse = lambda x: f'{indent}devices.{x}.second = "{x}";'
mid = ''.join(parse(x) for x in device_names)

devices_raw = pre + mid + post

with open(r"src\Devices.hpp", "w") as f:
	f.write(devices_raw)

time.sleep(1.0)