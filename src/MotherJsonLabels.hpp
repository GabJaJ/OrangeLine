/*
	MotherJsonLabels.hpp
 
	Code for the OrangeLine module Mother

Copyright (C) 2019 Dieter Stubler

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
	#pragma GCC diagnostic push 
	#pragma GCC diagnostic ignored "-Wwrite-strings"
	char *jsonLabel[NUM_JSONS] = {
		"style",
		/*
			Python gen:
			
				g = ""
				sd = "\t\t"
				for scale in range(1,13):
						g = g + sd
						nd = ""
						for note in range(0,12):
								g = g + nd + '"s' + ("00" + str(scale))[-2:] + "n" + ("00" + str(note))[-2:] + '"'
								nd = ", "
						sd = ",\n\t\t"
				g = g + ",\n"
				sd = "\t\t"
				for scale in range(1,13):
					g = g + sd
					cd = ""
					for child in range(0,12):
						g = g + cd
						wd = ""
						for weight in range(0,12):
							g = g + wd + '"s' + ("00" + str(scale))[-2:] + "c" + ("00" + str(child))[-2:] + "w" + ("00" + str(weight))[-2:] +'"'
							wd = ", "
						cd = ",\n\t\t"
					sd = ",\n\t\t"
				print g
		*/
		"s01n00", "s01n01", "s01n02", "s01n03", "s01n04", "s01n05", "s01n06", "s01n07", "s01n08", "s01n09", "s01n10", "s01n11",
		"s02n00", "s02n01", "s02n02", "s02n03", "s02n04", "s02n05", "s02n06", "s02n07", "s02n08", "s02n09", "s02n10", "s02n11",
		"s03n00", "s03n01", "s03n02", "s03n03", "s03n04", "s03n05", "s03n06", "s03n07", "s03n08", "s03n09", "s03n10", "s03n11",
		"s04n00", "s04n01", "s04n02", "s04n03", "s04n04", "s04n05", "s04n06", "s04n07", "s04n08", "s04n09", "s04n10", "s04n11",
		"s05n00", "s05n01", "s05n02", "s05n03", "s05n04", "s05n05", "s05n06", "s05n07", "s05n08", "s05n09", "s05n10", "s05n11",
		"s06n00", "s06n01", "s06n02", "s06n03", "s06n04", "s06n05", "s06n06", "s06n07", "s06n08", "s06n09", "s06n10", "s06n11",
		"s07n00", "s07n01", "s07n02", "s07n03", "s07n04", "s07n05", "s07n06", "s07n07", "s07n08", "s07n09", "s07n10", "s07n11",
		"s08n00", "s08n01", "s08n02", "s08n03", "s08n04", "s08n05", "s08n06", "s08n07", "s08n08", "s08n09", "s08n10", "s08n11",
		"s09n00", "s09n01", "s09n02", "s09n03", "s09n04", "s09n05", "s09n06", "s09n07", "s09n08", "s09n09", "s09n10", "s09n11",
		"s10n00", "s10n01", "s10n02", "s10n03", "s10n04", "s10n05", "s10n06", "s10n07", "s10n08", "s10n09", "s10n10", "s10n11",
		"s11n00", "s11n01", "s11n02", "s11n03", "s11n04", "s11n05", "s11n06", "s11n07", "s11n08", "s11n09", "s11n10", "s11n11",
		"s12n00", "s12n01", "s12n02", "s12n03", "s12n04", "s12n05", "s12n06", "s12n07", "s12n08", "s12n09", "s12n10", "s12n11",
		"s01c00w00", "s01c00w01", "s01c00w02", "s01c00w03", "s01c00w04", "s01c00w05", "s01c00w06", "s01c00w07", "s01c00w08", "s01c00w09", "s01c00w10", "s01c00w11",
		"s01c01w00", "s01c01w01", "s01c01w02", "s01c01w03", "s01c01w04", "s01c01w05", "s01c01w06", "s01c01w07", "s01c01w08", "s01c01w09", "s01c01w10", "s01c01w11",
		"s01c02w00", "s01c02w01", "s01c02w02", "s01c02w03", "s01c02w04", "s01c02w05", "s01c02w06", "s01c02w07", "s01c02w08", "s01c02w09", "s01c02w10", "s01c02w11",
		"s01c03w00", "s01c03w01", "s01c03w02", "s01c03w03", "s01c03w04", "s01c03w05", "s01c03w06", "s01c03w07", "s01c03w08", "s01c03w09", "s01c03w10", "s01c03w11",
		"s01c04w00", "s01c04w01", "s01c04w02", "s01c04w03", "s01c04w04", "s01c04w05", "s01c04w06", "s01c04w07", "s01c04w08", "s01c04w09", "s01c04w10", "s01c04w11",
		"s01c05w00", "s01c05w01", "s01c05w02", "s01c05w03", "s01c05w04", "s01c05w05", "s01c05w06", "s01c05w07", "s01c05w08", "s01c05w09", "s01c05w10", "s01c05w11",
		"s01c06w00", "s01c06w01", "s01c06w02", "s01c06w03", "s01c06w04", "s01c06w05", "s01c06w06", "s01c06w07", "s01c06w08", "s01c06w09", "s01c06w10", "s01c06w11",
		"s01c07w00", "s01c07w01", "s01c07w02", "s01c07w03", "s01c07w04", "s01c07w05", "s01c07w06", "s01c07w07", "s01c07w08", "s01c07w09", "s01c07w10", "s01c07w11",
		"s01c08w00", "s01c08w01", "s01c08w02", "s01c08w03", "s01c08w04", "s01c08w05", "s01c08w06", "s01c08w07", "s01c08w08", "s01c08w09", "s01c08w10", "s01c08w11",
		"s01c09w00", "s01c09w01", "s01c09w02", "s01c09w03", "s01c09w04", "s01c09w05", "s01c09w06", "s01c09w07", "s01c09w08", "s01c09w09", "s01c09w10", "s01c09w11",
		"s01c10w00", "s01c10w01", "s01c10w02", "s01c10w03", "s01c10w04", "s01c10w05", "s01c10w06", "s01c10w07", "s01c10w08", "s01c10w09", "s01c10w10", "s01c10w11",
		"s01c11w00", "s01c11w01", "s01c11w02", "s01c11w03", "s01c11w04", "s01c11w05", "s01c11w06", "s01c11w07", "s01c11w08", "s01c11w09", "s01c11w10", "s01c11w11",
		"s02c00w00", "s02c00w01", "s02c00w02", "s02c00w03", "s02c00w04", "s02c00w05", "s02c00w06", "s02c00w07", "s02c00w08", "s02c00w09", "s02c00w10", "s02c00w11",
		"s02c01w00", "s02c01w01", "s02c01w02", "s02c01w03", "s02c01w04", "s02c01w05", "s02c01w06", "s02c01w07", "s02c01w08", "s02c01w09", "s02c01w10", "s02c01w11",
		"s02c02w00", "s02c02w01", "s02c02w02", "s02c02w03", "s02c02w04", "s02c02w05", "s02c02w06", "s02c02w07", "s02c02w08", "s02c02w09", "s02c02w10", "s02c02w11",
		"s02c03w00", "s02c03w01", "s02c03w02", "s02c03w03", "s02c03w04", "s02c03w05", "s02c03w06", "s02c03w07", "s02c03w08", "s02c03w09", "s02c03w10", "s02c03w11",
		"s02c04w00", "s02c04w01", "s02c04w02", "s02c04w03", "s02c04w04", "s02c04w05", "s02c04w06", "s02c04w07", "s02c04w08", "s02c04w09", "s02c04w10", "s02c04w11",
		"s02c05w00", "s02c05w01", "s02c05w02", "s02c05w03", "s02c05w04", "s02c05w05", "s02c05w06", "s02c05w07", "s02c05w08", "s02c05w09", "s02c05w10", "s02c05w11",
		"s02c06w00", "s02c06w01", "s02c06w02", "s02c06w03", "s02c06w04", "s02c06w05", "s02c06w06", "s02c06w07", "s02c06w08", "s02c06w09", "s02c06w10", "s02c06w11",
		"s02c07w00", "s02c07w01", "s02c07w02", "s02c07w03", "s02c07w04", "s02c07w05", "s02c07w06", "s02c07w07", "s02c07w08", "s02c07w09", "s02c07w10", "s02c07w11",
		"s02c08w00", "s02c08w01", "s02c08w02", "s02c08w03", "s02c08w04", "s02c08w05", "s02c08w06", "s02c08w07", "s02c08w08", "s02c08w09", "s02c08w10", "s02c08w11",
		"s02c09w00", "s02c09w01", "s02c09w02", "s02c09w03", "s02c09w04", "s02c09w05", "s02c09w06", "s02c09w07", "s02c09w08", "s02c09w09", "s02c09w10", "s02c09w11",
		"s02c10w00", "s02c10w01", "s02c10w02", "s02c10w03", "s02c10w04", "s02c10w05", "s02c10w06", "s02c10w07", "s02c10w08", "s02c10w09", "s02c10w10", "s02c10w11",
		"s02c11w00", "s02c11w01", "s02c11w02", "s02c11w03", "s02c11w04", "s02c11w05", "s02c11w06", "s02c11w07", "s02c11w08", "s02c11w09", "s02c11w10", "s02c11w11",
		"s03c00w00", "s03c00w01", "s03c00w02", "s03c00w03", "s03c00w04", "s03c00w05", "s03c00w06", "s03c00w07", "s03c00w08", "s03c00w09", "s03c00w10", "s03c00w11",
		"s03c01w00", "s03c01w01", "s03c01w02", "s03c01w03", "s03c01w04", "s03c01w05", "s03c01w06", "s03c01w07", "s03c01w08", "s03c01w09", "s03c01w10", "s03c01w11",
		"s03c02w00", "s03c02w01", "s03c02w02", "s03c02w03", "s03c02w04", "s03c02w05", "s03c02w06", "s03c02w07", "s03c02w08", "s03c02w09", "s03c02w10", "s03c02w11",
		"s03c03w00", "s03c03w01", "s03c03w02", "s03c03w03", "s03c03w04", "s03c03w05", "s03c03w06", "s03c03w07", "s03c03w08", "s03c03w09", "s03c03w10", "s03c03w11",
		"s03c04w00", "s03c04w01", "s03c04w02", "s03c04w03", "s03c04w04", "s03c04w05", "s03c04w06", "s03c04w07", "s03c04w08", "s03c04w09", "s03c04w10", "s03c04w11",
		"s03c05w00", "s03c05w01", "s03c05w02", "s03c05w03", "s03c05w04", "s03c05w05", "s03c05w06", "s03c05w07", "s03c05w08", "s03c05w09", "s03c05w10", "s03c05w11",
		"s03c06w00", "s03c06w01", "s03c06w02", "s03c06w03", "s03c06w04", "s03c06w05", "s03c06w06", "s03c06w07", "s03c06w08", "s03c06w09", "s03c06w10", "s03c06w11",
		"s03c07w00", "s03c07w01", "s03c07w02", "s03c07w03", "s03c07w04", "s03c07w05", "s03c07w06", "s03c07w07", "s03c07w08", "s03c07w09", "s03c07w10", "s03c07w11",
		"s03c08w00", "s03c08w01", "s03c08w02", "s03c08w03", "s03c08w04", "s03c08w05", "s03c08w06", "s03c08w07", "s03c08w08", "s03c08w09", "s03c08w10", "s03c08w11",
		"s03c09w00", "s03c09w01", "s03c09w02", "s03c09w03", "s03c09w04", "s03c09w05", "s03c09w06", "s03c09w07", "s03c09w08", "s03c09w09", "s03c09w10", "s03c09w11",
		"s03c10w00", "s03c10w01", "s03c10w02", "s03c10w03", "s03c10w04", "s03c10w05", "s03c10w06", "s03c10w07", "s03c10w08", "s03c10w09", "s03c10w10", "s03c10w11",
		"s03c11w00", "s03c11w01", "s03c11w02", "s03c11w03", "s03c11w04", "s03c11w05", "s03c11w06", "s03c11w07", "s03c11w08", "s03c11w09", "s03c11w10", "s03c11w11",
		"s04c00w00", "s04c00w01", "s04c00w02", "s04c00w03", "s04c00w04", "s04c00w05", "s04c00w06", "s04c00w07", "s04c00w08", "s04c00w09", "s04c00w10", "s04c00w11",
		"s04c01w00", "s04c01w01", "s04c01w02", "s04c01w03", "s04c01w04", "s04c01w05", "s04c01w06", "s04c01w07", "s04c01w08", "s04c01w09", "s04c01w10", "s04c01w11",
		"s04c02w00", "s04c02w01", "s04c02w02", "s04c02w03", "s04c02w04", "s04c02w05", "s04c02w06", "s04c02w07", "s04c02w08", "s04c02w09", "s04c02w10", "s04c02w11",
		"s04c03w00", "s04c03w01", "s04c03w02", "s04c03w03", "s04c03w04", "s04c03w05", "s04c03w06", "s04c03w07", "s04c03w08", "s04c03w09", "s04c03w10", "s04c03w11",
		"s04c04w00", "s04c04w01", "s04c04w02", "s04c04w03", "s04c04w04", "s04c04w05", "s04c04w06", "s04c04w07", "s04c04w08", "s04c04w09", "s04c04w10", "s04c04w11",
		"s04c05w00", "s04c05w01", "s04c05w02", "s04c05w03", "s04c05w04", "s04c05w05", "s04c05w06", "s04c05w07", "s04c05w08", "s04c05w09", "s04c05w10", "s04c05w11",
		"s04c06w00", "s04c06w01", "s04c06w02", "s04c06w03", "s04c06w04", "s04c06w05", "s04c06w06", "s04c06w07", "s04c06w08", "s04c06w09", "s04c06w10", "s04c06w11",
		"s04c07w00", "s04c07w01", "s04c07w02", "s04c07w03", "s04c07w04", "s04c07w05", "s04c07w06", "s04c07w07", "s04c07w08", "s04c07w09", "s04c07w10", "s04c07w11",
		"s04c08w00", "s04c08w01", "s04c08w02", "s04c08w03", "s04c08w04", "s04c08w05", "s04c08w06", "s04c08w07", "s04c08w08", "s04c08w09", "s04c08w10", "s04c08w11",
		"s04c09w00", "s04c09w01", "s04c09w02", "s04c09w03", "s04c09w04", "s04c09w05", "s04c09w06", "s04c09w07", "s04c09w08", "s04c09w09", "s04c09w10", "s04c09w11",
		"s04c10w00", "s04c10w01", "s04c10w02", "s04c10w03", "s04c10w04", "s04c10w05", "s04c10w06", "s04c10w07", "s04c10w08", "s04c10w09", "s04c10w10", "s04c10w11",
		"s04c11w00", "s04c11w01", "s04c11w02", "s04c11w03", "s04c11w04", "s04c11w05", "s04c11w06", "s04c11w07", "s04c11w08", "s04c11w09", "s04c11w10", "s04c11w11",
		"s05c00w00", "s05c00w01", "s05c00w02", "s05c00w03", "s05c00w04", "s05c00w05", "s05c00w06", "s05c00w07", "s05c00w08", "s05c00w09", "s05c00w10", "s05c00w11",
		"s05c01w00", "s05c01w01", "s05c01w02", "s05c01w03", "s05c01w04", "s05c01w05", "s05c01w06", "s05c01w07", "s05c01w08", "s05c01w09", "s05c01w10", "s05c01w11",
		"s05c02w00", "s05c02w01", "s05c02w02", "s05c02w03", "s05c02w04", "s05c02w05", "s05c02w06", "s05c02w07", "s05c02w08", "s05c02w09", "s05c02w10", "s05c02w11",
		"s05c03w00", "s05c03w01", "s05c03w02", "s05c03w03", "s05c03w04", "s05c03w05", "s05c03w06", "s05c03w07", "s05c03w08", "s05c03w09", "s05c03w10", "s05c03w11",
		"s05c04w00", "s05c04w01", "s05c04w02", "s05c04w03", "s05c04w04", "s05c04w05", "s05c04w06", "s05c04w07", "s05c04w08", "s05c04w09", "s05c04w10", "s05c04w11",
		"s05c05w00", "s05c05w01", "s05c05w02", "s05c05w03", "s05c05w04", "s05c05w05", "s05c05w06", "s05c05w07", "s05c05w08", "s05c05w09", "s05c05w10", "s05c05w11",
		"s05c06w00", "s05c06w01", "s05c06w02", "s05c06w03", "s05c06w04", "s05c06w05", "s05c06w06", "s05c06w07", "s05c06w08", "s05c06w09", "s05c06w10", "s05c06w11",
		"s05c07w00", "s05c07w01", "s05c07w02", "s05c07w03", "s05c07w04", "s05c07w05", "s05c07w06", "s05c07w07", "s05c07w08", "s05c07w09", "s05c07w10", "s05c07w11",
		"s05c08w00", "s05c08w01", "s05c08w02", "s05c08w03", "s05c08w04", "s05c08w05", "s05c08w06", "s05c08w07", "s05c08w08", "s05c08w09", "s05c08w10", "s05c08w11",
		"s05c09w00", "s05c09w01", "s05c09w02", "s05c09w03", "s05c09w04", "s05c09w05", "s05c09w06", "s05c09w07", "s05c09w08", "s05c09w09", "s05c09w10", "s05c09w11",
		"s05c10w00", "s05c10w01", "s05c10w02", "s05c10w03", "s05c10w04", "s05c10w05", "s05c10w06", "s05c10w07", "s05c10w08", "s05c10w09", "s05c10w10", "s05c10w11",
		"s05c11w00", "s05c11w01", "s05c11w02", "s05c11w03", "s05c11w04", "s05c11w05", "s05c11w06", "s05c11w07", "s05c11w08", "s05c11w09", "s05c11w10", "s05c11w11",
		"s06c00w00", "s06c00w01", "s06c00w02", "s06c00w03", "s06c00w04", "s06c00w05", "s06c00w06", "s06c00w07", "s06c00w08", "s06c00w09", "s06c00w10", "s06c00w11",
		"s06c01w00", "s06c01w01", "s06c01w02", "s06c01w03", "s06c01w04", "s06c01w05", "s06c01w06", "s06c01w07", "s06c01w08", "s06c01w09", "s06c01w10", "s06c01w11",
		"s06c02w00", "s06c02w01", "s06c02w02", "s06c02w03", "s06c02w04", "s06c02w05", "s06c02w06", "s06c02w07", "s06c02w08", "s06c02w09", "s06c02w10", "s06c02w11",
		"s06c03w00", "s06c03w01", "s06c03w02", "s06c03w03", "s06c03w04", "s06c03w05", "s06c03w06", "s06c03w07", "s06c03w08", "s06c03w09", "s06c03w10", "s06c03w11",
		"s06c04w00", "s06c04w01", "s06c04w02", "s06c04w03", "s06c04w04", "s06c04w05", "s06c04w06", "s06c04w07", "s06c04w08", "s06c04w09", "s06c04w10", "s06c04w11",
		"s06c05w00", "s06c05w01", "s06c05w02", "s06c05w03", "s06c05w04", "s06c05w05", "s06c05w06", "s06c05w07", "s06c05w08", "s06c05w09", "s06c05w10", "s06c05w11",
		"s06c06w00", "s06c06w01", "s06c06w02", "s06c06w03", "s06c06w04", "s06c06w05", "s06c06w06", "s06c06w07", "s06c06w08", "s06c06w09", "s06c06w10", "s06c06w11",
		"s06c07w00", "s06c07w01", "s06c07w02", "s06c07w03", "s06c07w04", "s06c07w05", "s06c07w06", "s06c07w07", "s06c07w08", "s06c07w09", "s06c07w10", "s06c07w11",
		"s06c08w00", "s06c08w01", "s06c08w02", "s06c08w03", "s06c08w04", "s06c08w05", "s06c08w06", "s06c08w07", "s06c08w08", "s06c08w09", "s06c08w10", "s06c08w11",
		"s06c09w00", "s06c09w01", "s06c09w02", "s06c09w03", "s06c09w04", "s06c09w05", "s06c09w06", "s06c09w07", "s06c09w08", "s06c09w09", "s06c09w10", "s06c09w11",
		"s06c10w00", "s06c10w01", "s06c10w02", "s06c10w03", "s06c10w04", "s06c10w05", "s06c10w06", "s06c10w07", "s06c10w08", "s06c10w09", "s06c10w10", "s06c10w11",
		"s06c11w00", "s06c11w01", "s06c11w02", "s06c11w03", "s06c11w04", "s06c11w05", "s06c11w06", "s06c11w07", "s06c11w08", "s06c11w09", "s06c11w10", "s06c11w11",
		"s07c00w00", "s07c00w01", "s07c00w02", "s07c00w03", "s07c00w04", "s07c00w05", "s07c00w06", "s07c00w07", "s07c00w08", "s07c00w09", "s07c00w10", "s07c00w11",
		"s07c01w00", "s07c01w01", "s07c01w02", "s07c01w03", "s07c01w04", "s07c01w05", "s07c01w06", "s07c01w07", "s07c01w08", "s07c01w09", "s07c01w10", "s07c01w11",
		"s07c02w00", "s07c02w01", "s07c02w02", "s07c02w03", "s07c02w04", "s07c02w05", "s07c02w06", "s07c02w07", "s07c02w08", "s07c02w09", "s07c02w10", "s07c02w11",
		"s07c03w00", "s07c03w01", "s07c03w02", "s07c03w03", "s07c03w04", "s07c03w05", "s07c03w06", "s07c03w07", "s07c03w08", "s07c03w09", "s07c03w10", "s07c03w11",
		"s07c04w00", "s07c04w01", "s07c04w02", "s07c04w03", "s07c04w04", "s07c04w05", "s07c04w06", "s07c04w07", "s07c04w08", "s07c04w09", "s07c04w10", "s07c04w11",
		"s07c05w00", "s07c05w01", "s07c05w02", "s07c05w03", "s07c05w04", "s07c05w05", "s07c05w06", "s07c05w07", "s07c05w08", "s07c05w09", "s07c05w10", "s07c05w11",
		"s07c06w00", "s07c06w01", "s07c06w02", "s07c06w03", "s07c06w04", "s07c06w05", "s07c06w06", "s07c06w07", "s07c06w08", "s07c06w09", "s07c06w10", "s07c06w11",
		"s07c07w00", "s07c07w01", "s07c07w02", "s07c07w03", "s07c07w04", "s07c07w05", "s07c07w06", "s07c07w07", "s07c07w08", "s07c07w09", "s07c07w10", "s07c07w11",
		"s07c08w00", "s07c08w01", "s07c08w02", "s07c08w03", "s07c08w04", "s07c08w05", "s07c08w06", "s07c08w07", "s07c08w08", "s07c08w09", "s07c08w10", "s07c08w11",
		"s07c09w00", "s07c09w01", "s07c09w02", "s07c09w03", "s07c09w04", "s07c09w05", "s07c09w06", "s07c09w07", "s07c09w08", "s07c09w09", "s07c09w10", "s07c09w11",
		"s07c10w00", "s07c10w01", "s07c10w02", "s07c10w03", "s07c10w04", "s07c10w05", "s07c10w06", "s07c10w07", "s07c10w08", "s07c10w09", "s07c10w10", "s07c10w11",
		"s07c11w00", "s07c11w01", "s07c11w02", "s07c11w03", "s07c11w04", "s07c11w05", "s07c11w06", "s07c11w07", "s07c11w08", "s07c11w09", "s07c11w10", "s07c11w11",
		"s08c00w00", "s08c00w01", "s08c00w02", "s08c00w03", "s08c00w04", "s08c00w05", "s08c00w06", "s08c00w07", "s08c00w08", "s08c00w09", "s08c00w10", "s08c00w11",
		"s08c01w00", "s08c01w01", "s08c01w02", "s08c01w03", "s08c01w04", "s08c01w05", "s08c01w06", "s08c01w07", "s08c01w08", "s08c01w09", "s08c01w10", "s08c01w11",
		"s08c02w00", "s08c02w01", "s08c02w02", "s08c02w03", "s08c02w04", "s08c02w05", "s08c02w06", "s08c02w07", "s08c02w08", "s08c02w09", "s08c02w10", "s08c02w11",
		"s08c03w00", "s08c03w01", "s08c03w02", "s08c03w03", "s08c03w04", "s08c03w05", "s08c03w06", "s08c03w07", "s08c03w08", "s08c03w09", "s08c03w10", "s08c03w11",
		"s08c04w00", "s08c04w01", "s08c04w02", "s08c04w03", "s08c04w04", "s08c04w05", "s08c04w06", "s08c04w07", "s08c04w08", "s08c04w09", "s08c04w10", "s08c04w11",
		"s08c05w00", "s08c05w01", "s08c05w02", "s08c05w03", "s08c05w04", "s08c05w05", "s08c05w06", "s08c05w07", "s08c05w08", "s08c05w09", "s08c05w10", "s08c05w11",
		"s08c06w00", "s08c06w01", "s08c06w02", "s08c06w03", "s08c06w04", "s08c06w05", "s08c06w06", "s08c06w07", "s08c06w08", "s08c06w09", "s08c06w10", "s08c06w11",
		"s08c07w00", "s08c07w01", "s08c07w02", "s08c07w03", "s08c07w04", "s08c07w05", "s08c07w06", "s08c07w07", "s08c07w08", "s08c07w09", "s08c07w10", "s08c07w11",
		"s08c08w00", "s08c08w01", "s08c08w02", "s08c08w03", "s08c08w04", "s08c08w05", "s08c08w06", "s08c08w07", "s08c08w08", "s08c08w09", "s08c08w10", "s08c08w11",
		"s08c09w00", "s08c09w01", "s08c09w02", "s08c09w03", "s08c09w04", "s08c09w05", "s08c09w06", "s08c09w07", "s08c09w08", "s08c09w09", "s08c09w10", "s08c09w11",
		"s08c10w00", "s08c10w01", "s08c10w02", "s08c10w03", "s08c10w04", "s08c10w05", "s08c10w06", "s08c10w07", "s08c10w08", "s08c10w09", "s08c10w10", "s08c10w11",
		"s08c11w00", "s08c11w01", "s08c11w02", "s08c11w03", "s08c11w04", "s08c11w05", "s08c11w06", "s08c11w07", "s08c11w08", "s08c11w09", "s08c11w10", "s08c11w11",
		"s09c00w00", "s09c00w01", "s09c00w02", "s09c00w03", "s09c00w04", "s09c00w05", "s09c00w06", "s09c00w07", "s09c00w08", "s09c00w09", "s09c00w10", "s09c00w11",
		"s09c01w00", "s09c01w01", "s09c01w02", "s09c01w03", "s09c01w04", "s09c01w05", "s09c01w06", "s09c01w07", "s09c01w08", "s09c01w09", "s09c01w10", "s09c01w11",
		"s09c02w00", "s09c02w01", "s09c02w02", "s09c02w03", "s09c02w04", "s09c02w05", "s09c02w06", "s09c02w07", "s09c02w08", "s09c02w09", "s09c02w10", "s09c02w11",
		"s09c03w00", "s09c03w01", "s09c03w02", "s09c03w03", "s09c03w04", "s09c03w05", "s09c03w06", "s09c03w07", "s09c03w08", "s09c03w09", "s09c03w10", "s09c03w11",
		"s09c04w00", "s09c04w01", "s09c04w02", "s09c04w03", "s09c04w04", "s09c04w05", "s09c04w06", "s09c04w07", "s09c04w08", "s09c04w09", "s09c04w10", "s09c04w11",
		"s09c05w00", "s09c05w01", "s09c05w02", "s09c05w03", "s09c05w04", "s09c05w05", "s09c05w06", "s09c05w07", "s09c05w08", "s09c05w09", "s09c05w10", "s09c05w11",
		"s09c06w00", "s09c06w01", "s09c06w02", "s09c06w03", "s09c06w04", "s09c06w05", "s09c06w06", "s09c06w07", "s09c06w08", "s09c06w09", "s09c06w10", "s09c06w11",
		"s09c07w00", "s09c07w01", "s09c07w02", "s09c07w03", "s09c07w04", "s09c07w05", "s09c07w06", "s09c07w07", "s09c07w08", "s09c07w09", "s09c07w10", "s09c07w11",
		"s09c08w00", "s09c08w01", "s09c08w02", "s09c08w03", "s09c08w04", "s09c08w05", "s09c08w06", "s09c08w07", "s09c08w08", "s09c08w09", "s09c08w10", "s09c08w11",
		"s09c09w00", "s09c09w01", "s09c09w02", "s09c09w03", "s09c09w04", "s09c09w05", "s09c09w06", "s09c09w07", "s09c09w08", "s09c09w09", "s09c09w10", "s09c09w11",
		"s09c10w00", "s09c10w01", "s09c10w02", "s09c10w03", "s09c10w04", "s09c10w05", "s09c10w06", "s09c10w07", "s09c10w08", "s09c10w09", "s09c10w10", "s09c10w11",
		"s09c11w00", "s09c11w01", "s09c11w02", "s09c11w03", "s09c11w04", "s09c11w05", "s09c11w06", "s09c11w07", "s09c11w08", "s09c11w09", "s09c11w10", "s09c11w11",
		"s10c00w00", "s10c00w01", "s10c00w02", "s10c00w03", "s10c00w04", "s10c00w05", "s10c00w06", "s10c00w07", "s10c00w08", "s10c00w09", "s10c00w10", "s10c00w11",
		"s10c01w00", "s10c01w01", "s10c01w02", "s10c01w03", "s10c01w04", "s10c01w05", "s10c01w06", "s10c01w07", "s10c01w08", "s10c01w09", "s10c01w10", "s10c01w11",
		"s10c02w00", "s10c02w01", "s10c02w02", "s10c02w03", "s10c02w04", "s10c02w05", "s10c02w06", "s10c02w07", "s10c02w08", "s10c02w09", "s10c02w10", "s10c02w11",
		"s10c03w00", "s10c03w01", "s10c03w02", "s10c03w03", "s10c03w04", "s10c03w05", "s10c03w06", "s10c03w07", "s10c03w08", "s10c03w09", "s10c03w10", "s10c03w11",
		"s10c04w00", "s10c04w01", "s10c04w02", "s10c04w03", "s10c04w04", "s10c04w05", "s10c04w06", "s10c04w07", "s10c04w08", "s10c04w09", "s10c04w10", "s10c04w11",
		"s10c05w00", "s10c05w01", "s10c05w02", "s10c05w03", "s10c05w04", "s10c05w05", "s10c05w06", "s10c05w07", "s10c05w08", "s10c05w09", "s10c05w10", "s10c05w11",
		"s10c06w00", "s10c06w01", "s10c06w02", "s10c06w03", "s10c06w04", "s10c06w05", "s10c06w06", "s10c06w07", "s10c06w08", "s10c06w09", "s10c06w10", "s10c06w11",
		"s10c07w00", "s10c07w01", "s10c07w02", "s10c07w03", "s10c07w04", "s10c07w05", "s10c07w06", "s10c07w07", "s10c07w08", "s10c07w09", "s10c07w10", "s10c07w11",
		"s10c08w00", "s10c08w01", "s10c08w02", "s10c08w03", "s10c08w04", "s10c08w05", "s10c08w06", "s10c08w07", "s10c08w08", "s10c08w09", "s10c08w10", "s10c08w11",
		"s10c09w00", "s10c09w01", "s10c09w02", "s10c09w03", "s10c09w04", "s10c09w05", "s10c09w06", "s10c09w07", "s10c09w08", "s10c09w09", "s10c09w10", "s10c09w11",
		"s10c10w00", "s10c10w01", "s10c10w02", "s10c10w03", "s10c10w04", "s10c10w05", "s10c10w06", "s10c10w07", "s10c10w08", "s10c10w09", "s10c10w10", "s10c10w11",
		"s10c11w00", "s10c11w01", "s10c11w02", "s10c11w03", "s10c11w04", "s10c11w05", "s10c11w06", "s10c11w07", "s10c11w08", "s10c11w09", "s10c11w10", "s10c11w11",
		"s11c00w00", "s11c00w01", "s11c00w02", "s11c00w03", "s11c00w04", "s11c00w05", "s11c00w06", "s11c00w07", "s11c00w08", "s11c00w09", "s11c00w10", "s11c00w11",
		"s11c01w00", "s11c01w01", "s11c01w02", "s11c01w03", "s11c01w04", "s11c01w05", "s11c01w06", "s11c01w07", "s11c01w08", "s11c01w09", "s11c01w10", "s11c01w11",
		"s11c02w00", "s11c02w01", "s11c02w02", "s11c02w03", "s11c02w04", "s11c02w05", "s11c02w06", "s11c02w07", "s11c02w08", "s11c02w09", "s11c02w10", "s11c02w11",
		"s11c03w00", "s11c03w01", "s11c03w02", "s11c03w03", "s11c03w04", "s11c03w05", "s11c03w06", "s11c03w07", "s11c03w08", "s11c03w09", "s11c03w10", "s11c03w11",
		"s11c04w00", "s11c04w01", "s11c04w02", "s11c04w03", "s11c04w04", "s11c04w05", "s11c04w06", "s11c04w07", "s11c04w08", "s11c04w09", "s11c04w10", "s11c04w11",
		"s11c05w00", "s11c05w01", "s11c05w02", "s11c05w03", "s11c05w04", "s11c05w05", "s11c05w06", "s11c05w07", "s11c05w08", "s11c05w09", "s11c05w10", "s11c05w11",
		"s11c06w00", "s11c06w01", "s11c06w02", "s11c06w03", "s11c06w04", "s11c06w05", "s11c06w06", "s11c06w07", "s11c06w08", "s11c06w09", "s11c06w10", "s11c06w11",
		"s11c07w00", "s11c07w01", "s11c07w02", "s11c07w03", "s11c07w04", "s11c07w05", "s11c07w06", "s11c07w07", "s11c07w08", "s11c07w09", "s11c07w10", "s11c07w11",
		"s11c08w00", "s11c08w01", "s11c08w02", "s11c08w03", "s11c08w04", "s11c08w05", "s11c08w06", "s11c08w07", "s11c08w08", "s11c08w09", "s11c08w10", "s11c08w11",
		"s11c09w00", "s11c09w01", "s11c09w02", "s11c09w03", "s11c09w04", "s11c09w05", "s11c09w06", "s11c09w07", "s11c09w08", "s11c09w09", "s11c09w10", "s11c09w11",
		"s11c10w00", "s11c10w01", "s11c10w02", "s11c10w03", "s11c10w04", "s11c10w05", "s11c10w06", "s11c10w07", "s11c10w08", "s11c10w09", "s11c10w10", "s11c10w11",
		"s11c11w00", "s11c11w01", "s11c11w02", "s11c11w03", "s11c11w04", "s11c11w05", "s11c11w06", "s11c11w07", "s11c11w08", "s11c11w09", "s11c11w10", "s11c11w11",
		"s12c00w00", "s12c00w01", "s12c00w02", "s12c00w03", "s12c00w04", "s12c00w05", "s12c00w06", "s12c00w07", "s12c00w08", "s12c00w09", "s12c00w10", "s12c00w11",
		"s12c01w00", "s12c01w01", "s12c01w02", "s12c01w03", "s12c01w04", "s12c01w05", "s12c01w06", "s12c01w07", "s12c01w08", "s12c01w09", "s12c01w10", "s12c01w11",
		"s12c02w00", "s12c02w01", "s12c02w02", "s12c02w03", "s12c02w04", "s12c02w05", "s12c02w06", "s12c02w07", "s12c02w08", "s12c02w09", "s12c02w10", "s12c02w11",
		"s12c03w00", "s12c03w01", "s12c03w02", "s12c03w03", "s12c03w04", "s12c03w05", "s12c03w06", "s12c03w07", "s12c03w08", "s12c03w09", "s12c03w10", "s12c03w11",
		"s12c04w00", "s12c04w01", "s12c04w02", "s12c04w03", "s12c04w04", "s12c04w05", "s12c04w06", "s12c04w07", "s12c04w08", "s12c04w09", "s12c04w10", "s12c04w11",
		"s12c05w00", "s12c05w01", "s12c05w02", "s12c05w03", "s12c05w04", "s12c05w05", "s12c05w06", "s12c05w07", "s12c05w08", "s12c05w09", "s12c05w10", "s12c05w11",
		"s12c06w00", "s12c06w01", "s12c06w02", "s12c06w03", "s12c06w04", "s12c06w05", "s12c06w06", "s12c06w07", "s12c06w08", "s12c06w09", "s12c06w10", "s12c06w11",
		"s12c07w00", "s12c07w01", "s12c07w02", "s12c07w03", "s12c07w04", "s12c07w05", "s12c07w06", "s12c07w07", "s12c07w08", "s12c07w09", "s12c07w10", "s12c07w11",
		"s12c08w00", "s12c08w01", "s12c08w02", "s12c08w03", "s12c08w04", "s12c08w05", "s12c08w06", "s12c08w07", "s12c08w08", "s12c08w09", "s12c08w10", "s12c08w11",
		"s12c09w00", "s12c09w01", "s12c09w02", "s12c09w03", "s12c09w04", "s12c09w05", "s12c09w06", "s12c09w07", "s12c09w08", "s12c09w09", "s12c09w10", "s12c09w11",
		"s12c10w00", "s12c10w01", "s12c10w02", "s12c10w03", "s12c10w04", "s12c10w05", "s12c10w06", "s12c10w07", "s12c10w08", "s12c10w09", "s12c10w10", "s12c10w11",
		"s12c11w00", "s12c11w01", "s12c11w02", "s12c11w03", "s12c11w04", "s12c11w05", "s12c11w06", "s12c11w07", "s12c11w08", "s12c11w09", "s12c11w10", "s12c11w11"
	};
	#pragma GCC diagnostic pop
