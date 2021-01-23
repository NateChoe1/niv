# NIV, a text editor.
# Copyright (C) 2021  Nathaniel Choe
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the license, or
# {at your option} any later version.
# 
# This program is distribyted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.
# 
# Email me: natechoe9@gmail.com

niv: src/niv.c
	$(CC) src/niv.c -o build/niv -lncurses -O3
