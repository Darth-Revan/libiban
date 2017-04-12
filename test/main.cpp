/*
 * MIT License
 * Copyright (c) 2017 Kevin Kirchner
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * \file        main.cpp
 * \brief       The main test file and entry point for \p Catch
 * \author      Kevin Kirchner
 * \date        2017
 * \copyright   MIT LICENSE
 *
 * This file is the main test file for \p libiban and the entry point for
 * \p Catch.
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/libiban.h"
#include "../src/utils.h"

// Test case for trim function in utils.h
TEST_CASE("trim", "[utils]") {
    std::string test = "345 sdfnsf8 403  fsdfs \na\t asda";
    std::string test2 = "";
    std::string test3 = "\n\n \t asidas da4a sab sd94";
    std::string test4 = "abfOAHF48tadf";
    REQUIRE(trim(test) == "345sdfnsf8403fsdfsaasda");
    REQUIRE(trim(test2) == "");
    REQUIRE(trim(test3) == "asidasda4asabsd94");
    REQUIRE(trim(test4) == "abfOAHF48tadf");
}

// Test case for constructor
TEST_CASE("createFromString", "[libiban]") {
    IBAN::IBAN iban = IBAN::IBAN::createFromString("DE68 2105 0170 0012 3456 78");

    IBAN::IBAN iban2 = iban;
    REQUIRE(iban.getBBAN() == iban2.getBBAN());
    REQUIRE(iban.getCountryCode() == iban2.getCountryCode());
    REQUIRE(iban.getChecksum() == iban2.getChecksum());

    IBAN::IBAN iban3 = IBAN::IBAN::createFromString("DE68210501700012345678");
    REQUIRE(iban.getBBAN() == iban3.getBBAN());
    REQUIRE(iban.getCountryCode() == iban3.getCountryCode());
    REQUIRE(iban.getChecksum() == iban3.getChecksum());


    IBAN::IBAN iban4 = IBAN::IBAN::createFromString("AD43oh8445353ADF");
    REQUIRE(!iban4.getBBAN().empty());
    REQUIRE(!iban4.getCountryCode().empty());
    REQUIRE(!iban4.getChecksum().empty());

    try {
        IBAN::IBAN iban5 = IBAN::IBAN::createFromString("BLA");
    } catch (const IBAN::IBANParseException& ex) {
        REQUIRE(ex.what());
    }
    try {
        IBAN::IBAN iban6 = IBAN::IBAN::createFromString("B1af935395");
    } catch (const IBAN::IBANParseException& ex) {
        REQUIRE(ex.what());
    }
    try {
        IBAN::IBAN iban7 = IBAN::IBAN::createFromString("DE682105017000/2345678");
    } catch (const IBAN::IBANParseException& ex) {
        REQUIRE(ex.what());
    }
}

// Test case for comparison operators
TEST_CASE("Comparison operators", "[libiban]") {
    IBAN::IBAN iban = IBAN::IBAN::createFromString("DE68 2105 0170 0012 3456 78");
    IBAN::IBAN iban2 = IBAN::IBAN::createFromString("DE68210501700012345678");
    IBAN::IBAN iban3 = IBAN::IBAN::createFromString("LI4212345678901234567");
    REQUIRE(iban == iban2);
    REQUIRE(iban2 == iban);
    REQUIRE(iban != iban3);
    REQUIRE(iban3 != iban);
    REQUIRE(iban2 != iban3);
    REQUIRE(iban3 != iban2);
    REQUIRE(iban == iban);
}

// Test case for machine form output
TEST_CASE("getMachineForm", "[libiban]") {
    IBAN::IBAN iban = IBAN::IBAN::createFromString("DE68 2105 0170 0012 3456 78");
    REQUIRE(iban.getMachineForm() == "DE68210501700012345678");
    IBAN::IBAN iban2 = IBAN::IBAN::createFromString(" GB82 WEST 1234 5698 7654 32");
    REQUIRE(iban2.getMachineForm() == "GB82WEST12345698765432");
}

// Test case for human readable form output
TEST_CASE("getHumanReadable", "[libiban]") {
    IBAN::IBAN iban = IBAN::IBAN::createFromString("DE68 2105 0170 0012 3456 78");
    REQUIRE(iban.getHumanReadable() == "DE68 2105 0170 0012 3456 78");
    IBAN::IBAN iban2 = IBAN::IBAN::createFromString(" GB82 WEST 1234 5698 7654 32");
    REQUIRE(iban2.getHumanReadable() == "GB82 WEST 1234 5698 7654 32");
}

// Test cases for validation
TEST_CASE("validate", "[libiban]") {
    std::vector<std::string> valid = {
        "AL06202111090000000005012075", "AD1000060004451247870930",
        "AT021100000622888600", "AZ04UBAZ04003214540060AZN001",
        "BH02CITI00001077181611", "BE45096920886089",
        "BA391011606058553319", "BR0200000000010670000117668C1",
        "BG02RZBB91551002755190", "CR79015202220005614288",
        "HR0223400093216312031", "CY02002001950000357009822416",
        "CZ0201000000199216760237", "FO1291810001441878",
        "GL2664710001504964", "DK0220005036459478",
        "DO22BCBH00000000011003290022", "EE021700017000459042",
        "FI0210403500314392", "FR0220041000016219433J02076",
        "GE02TB7523045063700002", "DE02100500000024290661",
        "GI04BARC020452163087000", "GR0201102160000021661309175",
        "GT24CITI01010000000004146026", "HU02116000060000000064247067",
        "IS040116381002305610911109", "IE02BOFI90008413113207",
        "IL020108380000002149431", "IT43K0310412701000000820420",
        "JO02SCBL1260000000018525836101", "KZ04319C010005569698",
        "KW02NBOK0000000000001000614589", "LV02HABA0551007820897",
        "LB02001400000302300023018319", "LI0308800000022875748",
        "LT027300010134441147", "LU020019175546294000",
        "MK07200000625758632", "MT02VALL22013000000040013752732",
        "MR1300012000010000009880016", "MU03MCBL0901000001879025000USD",
        "MD14MO2224ASV41884097100", "MC2412739000710075018000P14",
        "ME25505120000000466170", "NL02ABNA0457180536",
        "NO0239916835985", "PK02SCBL0000001925518401",
        "PS06ARAB000000009040781605610", "PL02103000190109780401676562",
        "PT50003600409911001102673", "QA03QNBA000000000060565452001",
        "RO02BRDE445SV75163474450", "SM07U0854009803000030174419",
        "LC55HEMM000100010012001200023015", "ST23000200000289355710148",
        "SA0220000002480647579940", "RS35105008054113238018",
        "SK0202000000003679748552", "SI56011006000005649",
        "ES1321000555370200853027", "SE0230000000030301099952",
        "CH020020720710117540C", "TL380030000000025923744",
        "TN5901026067111999766058", "TR020001000201529153355002",
        "AE020090004001079346500", "GB11CITI18500811417983",
        "VG48NOSC0000000005002993", "UA123052990004149497803982794",
        "SC74NOVH00000021002035257028SCR", "IQ20CBIQ861800101010500",
        "BY86AKBB10100000002966000000", "SV43ACAT00000000000000123123",
        "BE68539007547034", "BJ11B00610100400271101192591",
        "BR9700360305000010009795493P1", "BG80BNBG96611020345678",
        "BF42BF0840101300463574000390", "BI43201011067444",
        "CM2110003001000500000605306", "CV64000300004547069110176",
        "HR1210010051863000160", "CY17002001280000001200527600",
        "CZ6508000000192000145399", "DK5000400440116243",
        "DO28BAGR00000001212453611324", "TL380080012345678910157",
        "EE382200221020145685", "FO1464600009692713",
        "FI2112345600000785", "FR1420041010050500013M02606",
        "GT82TRAJ01020000001210029690", "GE29NB0000000101904917",
        "DE89370400440532013000", "GI75NWBK000000007099453",
        "GR1601101250000000012300695", "GL8964710001000206",
        "HU42117730161111101800000000", "IS140159260076545510730339",
        "IR580540105180021273113007", "IE29AIBK93115212345678",
        "IL620108000000099999999", "IT60X0542811101000000123456",
        "CI93CI0080111301134291200589", "JO94CBJO0010000000000131000302",
        "KZ176010251000042993", "KW74NBOK0000000000001000372151",
        "LV80BANK0000435195001", "LB30099900000001001925579115",
        "LI21088100002324013AA", "LT121000011101001000",
        "LU280019400644750000", "MG4600005030010101914016056",
        "MT84MALT011000012345MTLCAST001S", "MR1300012000010000002037372",
        "MU17BOMM0101101030300200000MUR", "ML13ML0160120102600100668497",
        "MD24AG000225100013104168", "MC5813488000010051108001292",
        "ME25505000012345678951", "MZ59000100000011834194157",
        "NL91ABNA0417164300", "NO9386011117947",
        "PK24SCBL0000001171495101", "PS92PALS000000000400123456702",
        "PL27114020040000300201355387", "PT50000201231234567890154",
        "QA58DOHB00001234567890ABCDEFG", "XK051301001002074155",
        "RO49AAAA1B31007593840000", "SM86U0322509800000000270100",
        "SN12K00100152000025690007542", "RS35260005601001611379",
        "SK3112000000198742637541", "SI56191000000123438",
        "ES9121000418450200051332", "SE3550000000054910000003",
        "CH9300762011623852957", "TN5914207207100707129648",
        "TR330006100519786457841326", "AE260211000000230064016",
        "GB29NWBK60161331926819", "VG96VPVG0000012345678901",
        "DE68 2105 0170 0012 3456 78", " GB82 WEST 1234 5698 7654 32",
        "AO06004400006729503010102", "BF42BF0840101300463574000390",
        "BI43201011067444", "BJ66BJ0610100100144390000769",
        "CF4220001000010120069700160", "CG3930011000101013451300019",
        "CI93CI0080111301134291200589", "CM2110002000300277976315008",
        "CV64000500000020108215144", "EG2100037000671002392189379",
        "DJ2110002010010409943020008", "DZ5802100017115005701653",
        "GA2140021010032001890020126", "GQ7050002001003715228190196",
        "GW04GW1430010181800637601", "IR710570029971601460641001",
        "MA64011519000001205000534921", "MG4600005030071289421016045",
        "ML13ML0160120102600100668497", "MZ59000301080016367102371",
        "NE58NE0380100100130305000268", "SN08SN0100152000048500003035",
        "TD8960002000010271091600153", "TG53TG0090604310346500400070",
        "KM4600005000010010904400137", "HN54PISA00000000000000123124",
        "NI92BAMC000000000000000003123123",
    };
    std::vector<std::string> invalid = {
        "GB82TEST12345698765432", "DE68 2105 0170 0012 3456 7",
        "AL0620211d090000000005012075", "AD1000060003451247870930",
        "AT021100000622888700", "AZ04UBAZ04003214520060AZN001",
        "BH02CITI00001077151611", "BE45096920886189",
        "BX391011606058553319", "BR020000000010670000117668C1",
        "ZT02RZBB91551002755190", "CR79015202120005614288",
        "IS04011638102305610911109", "IE02BOI90008413113207",
        "IL02010838000002149431", "IT43K031412701000000820420",
        "JO02SCBL126000000018525836101", "KZ0439C010005569698",
        "KW02NBOK000000000000100614589", "LV02HABA0B51007820897",
        "LB02001400000302300021018319", "LI030880A000022875748",
        "LT02730001013444114Y", "LU020019175546A94000",
        "MK07200000625754632", "MT02VALL2201300000004A013752732",
        "MR13000120000100F0009880016", "MU03MCBL0901G00001879025000USD",
        "MD14MO2224ASV41A84097100", "MC241273000710075018000P14",
        "ME2550510000000466170", "NL02ABNA047180536",
        "NO023991635985", "PK02SCBL000000192518401",
        "PS06ARAB00000009040781605610", "PL0210300010109780401676562",
        "PW50003600409911001102673", "QA05QNBA000000000060565452001",
        "RQ02BRDE445SV75163474450", "SM07R0854009803000030174419",
        "LC55HEMM0001000100R2001200023015", "ST03000200000289355710148",
        "SA0220000002480647R79940", "HS35105008054113238018",
        "SK020200000003679748552", "SI5601100000005649",
        "ES132100055537000853027", "SE230000000030301099952",
        "CH02002072071017540C", "TL38003000000025923744",
        "TN590102606711999766058", "TR02000100201529153355002",
        "AE020090004001059346500", "GB11CIT38500811417983",
        "VG48NOSC0000000105002993", "UA12305690004149497803982794",
        "SC74NOVH00000023002035257028SCR", "Ia20CBIQ861800101010500",
        "BY86AKBB10100007002966000000", "SF43ACAT00000000000000123123",
        "BE68539007547044", "BJ11B00611100400271101192591",
        "ZR9700360305000010009795493P1", "BG80BNBG96e611020345678",
        "BF32BF0840101300463574000390", "BI4320101106e7444",
        "CM211000300100050000605306", "CV640003300004547069110176",
        "HR12100510051863000160", "CY170020012c80000001200527600",
        "CZ65087000000192000145399", "DK500040044a0116243",
        "DO28BAGR0000001212453611324", "TL3800180012345678910157",
        "EE38220022020145685", "FO3146460d0009692713",
        "FI211234560000785", "FR1420a041010050500013M02606",
        "GT82TRAJ0102000001210029690", "GR29NB000000010d1904917",
        "DE89370450532013000", "GI75NWBK0000077099453",
        "GR16011350000000012300695", "GL89647171000206",
        "HU4211773016111130000", "IS1401570076545510730339",
        "IR5805401055021273113007", "IE29AIBK9G15212345678",
        "IL62010800030099999999", "IT60X05428501000000123456",
        "CI93CI0080211301134291200589", "JO94CBJO0010000HE0000131000302",
        "KZ17601025500042993", "KW74NBOK000000HL200001000372151",
        "LV80BANK030435195001", "LB30099HL3000001001925579115",
        "LI2108810H02324013AA", "LT1210000TR1001000",
        "LU28001940GF44750000", "MG460000503002101914016056",
        "MT84MALT011002345MTLCAST001S", "MR1300012000GF000002037372",
        "MU17BOMM0101D30300200000MUR", "ML13ML01TR0102600100668497",
        "MD24AG00022F013104168", "MC581348800T0051108001292",
        "ME2550500A12345678951", "MZ590001sd00011834194157",
        "NL91ABNA057164300", "NO9386FD1117947",
        "CH930076201A3852957", "TN59142072d0707129648",
        "TR33000610051786457841326", "AE260211000230064016",
        "GB29NWBK6016131926819", "VG96VPVG00012345678901",
        "DE68 2105 01 0012 3456 78", " GB82EST 1234 5698 7654 32",
        "AO0600440000672950510102", "BF42B0840101300463574000390",
        "BI432010110674441", "BJ66BJ06101001001443900007692",
        "CF42200010000101200697001603", "CG39300110001010134513000194",
        "CI93CI00801113011342912005895", "CM21100020003002779763150086",
        "CV640005000000201082151447", "EG21000370006710023921893798",
        "DJ21100020100104099430200080", "DZ58021000171150057016539",
    };

    for (const auto& str : valid) {
        auto num = IBAN::IBAN::createFromString(str);
        REQUIRE(num.validate());
    }
    for (const auto& str : invalid) {
        auto num = IBAN::IBAN::createFromString(str);
        REQUIRE(!num.validate());
    }
}
