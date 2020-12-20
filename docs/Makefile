# Copyright (C) 2020 Roman Ondráček <xondra58@stud.fit.vutbr.cz>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

PROJECT=docs
TEX=pdflatex

.PHONY: all clean cleanall

all:
	$(TEX) $(PROJECT).tex
	$(TEX) $(PROJECT).tex
clean:
	rm -f *.toc *.aux *.log *.dvi *.ps *.lot *.out *.znd *.zdx

cleanall:
	rm -f *.toc *.aux *.log *.dvi *.ps *.lot *.out *.znd *.zdx *.pdf
