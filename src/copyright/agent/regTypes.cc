/*
 * Copyright (C) 2014-2015, Siemens AG
 * Author: Johannes Najjar, Daniele Fognini
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "regTypes.hpp"


const  std::string regCopyright::getType(){
  return std::string("statement");
};


#define EMAILRGX  "[\\<\\(]?([\\w\\-\\.\\+]{1,100}@[\\w\\-\\.\\+]{1,100}\\.[a-z]{1,4})[\\>\\)]?"
#define WEBSITE  "(http|https|ftp)\\://[a-zA-Z0-9\\-\\.]+\\.[a-zA-Z]{2,4}(:[a-zA-Z0-9]*)?/?([a-zA-Z0-9\\-\\._\\?\\,\'/\\\\+&amp;%\\$#\\=~])*[^\\.\\,\\)\\(\\s]"

const std::string regCopyright::getRegex() {
#define SPACECLS          "[\\t ]"
#define SPACES            SPACECLS "+"
#define SPACESALL         "[[:space:]]*"
#define PUNCT_OR_SPACE    "[[:punct:][:space:]]"
#define ABBR_AND_BRACED   "[A-Z]{2,7}\\([^)]+\\)"
#define ALPHA             "[:alpha:]\u00c0-\u00d6\u00d9-\u00f6\u00f8-\u00ff"
#define NAME_OR_COMPANY   "((" ABBR_AND_BRACED ")|([" ALPHA "]{1,3}\\.)|Co[or]p\\.|([" ALPHA "]+)|(" EMAILRGX ")|(" WEBSITE "))"
#define NAMESLIST         NAME_OR_COMPANY "(([-, &]+)" NAME_OR_COMPANY ")*"
#define DATE              "((19|20)[[:digit:]]{2,2}|[[:digit:]]{1,2})"
#define DATESLIST         DATE "(([[:punct:][:space:]-]+)" DATE ")*"
#define COPYR_SYM_ALONE   "©|\xA9|\xC2\xA9" "|\\$\xB8|\xED\x92\xB8|\\$\xD2|\xE2\x93\x92" "|\\$\x9E|\xE2\x92\x9E"
#define COPYR_SYM         "(\\(c\\)|" COPYR_SYM_ALONE ")"
#define COPYR_TXT         "copyright(s)?"

 return std::string(
  "("
    "("
      "("
        COPYR_SYM "(" SPACESALL COPYR_TXT "|" SPACES DATESLIST ")"
        "|" COPYR_TXT ":?" SPACESALL COPYR_SYM
        "|" COPYR_TXT
        "|" COPYR_SYM_ALONE
      ")"
      "("
        SPACES
        "((and|hold|info|law|licen|message|notice|owner|state|string|tag|copy|permission|this|timestamp|@author)*)"
      ")?"
      "("
        PUNCT_OR_SPACE "?"
        SPACESALL
        DATESLIST
      ")?"
      "("
        PUNCT_OR_SPACE "?"
        SPACESALL
        NAMESLIST
      ")"
      "("
        PUNCT_OR_SPACE "?"
        SPACESALL
        DATESLIST
      ")?"
      "(" PUNCT_OR_SPACE"*" "all" SPACES "rights" SPACES "reserved)?"
    ")|("
      "("
        "((author|contributor|maintainer)s?)"
        "|((written|contribut(ed|ions?)|maintained|modifi(?:ed|cations?)|put" SPACES "together)" SPACES "by)"
      ")"
      "[:]?"
      SPACESALL
      NAMESLIST
    ")"
  ")"
  "\\.?"
 );
};

const  std::string regURL::getType(){
  return std::string("url");
};

const std::string regURL::getRegex() {
 return std::string(
             "(?:(:?ht|f)tps?\\:\\/\\/[^\\s\\<]+[^\\<\\.\\,\\s])"
 );
};


const  std::string regEmail::getType(){
  return std::string("email");
};

const std::string regEmail::getRegex() {
 return std::string(EMAILRGX);
};



const  std::string regIp::getType(){
  return std::string("ip");
};

const std::string regIp::getRegex() {
 return std::string(
   "("
    "(patent(ability|ed|ee|ing))"
    "|((US|EU)" SPACES "(PAT|patents))"
    "|(USPTO|PCT)"
    "|(invent(ion|or|ive))"
    "|(filed)"
    "|(innovation|infringement)"
    "|(intellectual" SPACES "property)"
    "|(prior" SPACES "art)"
    "|(field[-]of[-]use" SPACES "limitation)"
    "|(fair" SPACES "use)"
   ")"
   "[[:space:][:punct:]]+" // TODO what's the purpose of this???
   "[[:alpha:]]*"
   "[[:punct:]]*"
   "[[:alpha:]]*"
   "[[:space:]]*"
   "[[:print:]]{0,60}"     // \TODO
 );
};


const  std::string regEcc::getType(){
  return std::string("ecc");
};

const std::string regEcc::getRegex() {
 return std::string(
   "("
    "eccn|tsu|ecc|ccl|wco"
    "|(export" SPACES "control)"
    "|(customs)"
    "|(foreign" SPACES "trade(" SPACES "regulations)?)"
    "|(commerce" SPACES "control)"
    "|(country" SPACES "of" SPACES "origin)"
    "|(export" SPACES "administration)"
    "|((k|c)rypt)"
    "|(information" SPACES "security)"
    "|(encryption)"
    "|(nuclear|surveillance|military|defense|marine|avionics|laser)"
    "|(propulsion" SPACES "systems)"
    "|(space" SPACES "vehicle(s)?)"
    "|(dual" SPACES "use)"
   ")"
   "[^)\n]{0,60}"     // \TODO
 );
};