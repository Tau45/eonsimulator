#include "../../include/tools/SeedsProvider.h"

int32_t SeedsProvider::getSeed() {
	int32_t seed = seeds.front();
	seeds.pop();
	return seed;
}

uint64_t SeedsProvider::getNumberOfAvailableSeeds() {
	return seeds.size();
}

vector<int32_t> SeedsProvider::getSeedsForSingleSimulation() {
	vector<int32_t> seedsForSingleSimulation;
	for (uint64_t k = 0; k < 3; k++) {
		seedsForSingleSimulation.push_back(getSeed());
	}
	return seedsForSingleSimulation;
}

vector<vector<int32_t>> SeedsProvider::getSeedsForSimulationSet(uint64_t numberOfSimulationsInSet) {
	vector<vector<int32_t>> seedsForSimulationSet;
	for (uint64_t j = 0; j < numberOfSimulationsInSet; j++) {
		seedsForSimulationSet.push_back(getSeedsForSingleSimulation());
	}
	return seedsForSimulationSet;
}

vector<vector<vector<int32_t>>> SeedsProvider::getSeeds(uint64_t numberOfSimulationSets, uint64_t numberOfSimulationsPerSet) {
	vector<vector<vector<int32_t>>> seedVector;
	for (uint64_t i = 0; i < numberOfSimulationSets; i++) {
		seedVector.push_back(getSeedsForSimulationSet(numberOfSimulationsPerSet));
	}
	return seedVector;
}

SeedsProvider::SeedsProvider() {
	seeds.push(-294773772);
	seeds.push(1077881100);
	seeds.push(-1956909445);
	seeds.push(582622070);
	seeds.push(-766730045);
	seeds.push(-2059726178);
	seeds.push(-748573556);
	seeds.push(954279421);
	seeds.push(1510743385);
	seeds.push(1523496188);
	seeds.push(448134163);
	seeds.push(-27868987);
	seeds.push(758442625);
	seeds.push(-1313041142);
	seeds.push(1510579753);
	seeds.push(1971569848);
	seeds.push(-1352287989);
	seeds.push(552859471);
	seeds.push(1247292905);
	seeds.push(1720956229);
	seeds.push(-340843887);
	seeds.push(569032229);
	seeds.push(385363838);
	seeds.push(-1045444143);
	seeds.push(-404257609);
	seeds.push(-998213448);
	seeds.push(468993426);
	seeds.push(653563192);
	seeds.push(-1971216373);
	seeds.push(1303653592);
	seeds.push(890969127);
	seeds.push(-721466155);
	seeds.push(30539014);
	seeds.push(-540636414);
	seeds.push(277329856);
	seeds.push(513068556);
	seeds.push(894773947);
	seeds.push(84978925);
	seeds.push(-1658077757);
	seeds.push(-992323637);
	seeds.push(-222279030);
	seeds.push(657703549);
	seeds.push(1039347555);
	seeds.push(-233385973);
	seeds.push(1269194743);
	seeds.push(-833722538);
	seeds.push(1881297253);
	seeds.push(-748133599);
	seeds.push(85008902);
	seeds.push(-1425558605);
	seeds.push(-1088950374);
	seeds.push(1437615597);
	seeds.push(-1666209321);
	seeds.push(1278200949);
	seeds.push(-1590257878);
	seeds.push(-1259047185);
	seeds.push(-1330804762);
	seeds.push(900231162);
	seeds.push(561879930);
	seeds.push(1264546693);
	seeds.push(2026713289);
	seeds.push(722940450);
	seeds.push(-132071870);
	seeds.push(1304260839);
	seeds.push(683809513);
	seeds.push(1554584897);
	seeds.push(-1135584592);
	seeds.push(1679194129);
	seeds.push(-1789107463);
	seeds.push(2119829637);
	seeds.push(184521163);
	seeds.push(-2058925697);
	seeds.push(-1871384500);
	seeds.push(242240622);
	seeds.push(1317414229);
	seeds.push(312690927);
	seeds.push(-1493296510);
	seeds.push(-1204406035);
	seeds.push(161387225);
	seeds.push(-2135292670);
	seeds.push(886824390);
	seeds.push(271927261);
	seeds.push(-338480283);
	seeds.push(-1147048725);
	seeds.push(-271815680);
	seeds.push(-1231714614);
	seeds.push(-1473384685);
	seeds.push(-1423594551);
	seeds.push(1743481209);
	seeds.push(-1512587175);
	seeds.push(750789420);
	seeds.push(-1991525758);
	seeds.push(55003524);
	seeds.push(604845046);
	seeds.push(-1037030274);
	seeds.push(-131878041);
	seeds.push(1902704512);
	seeds.push(-1303273735);
	seeds.push(-394938151);
	seeds.push(-1230113473);
	seeds.push(526214861);
	seeds.push(641275200);
	seeds.push(977506039);
	seeds.push(-727436545);
	seeds.push(1260813652);
	seeds.push(943606659);
	seeds.push(-1725210462);
	seeds.push(1987035199);
	seeds.push(-1216142456);
	seeds.push(-1001075912);
	seeds.push(-2071908022);
	seeds.push(1746146770);
	seeds.push(-442048224);
	seeds.push(1343252481);
	seeds.push(-150697091);
	seeds.push(501064050);
	seeds.push(536162715);
	seeds.push(-2124831593);
	seeds.push(-1410606552);
	seeds.push(-1132287897);
	seeds.push(-535972542);
	seeds.push(-895661088);
	seeds.push(-382995550);
	seeds.push(1605029581);
	seeds.push(824002886);
	seeds.push(1600204608);
	seeds.push(1456091509);
	seeds.push(-1994121661);
	seeds.push(-672680349);
	seeds.push(60650189);
	seeds.push(-663653077);
	seeds.push(-1245348998);
	seeds.push(1288162084);
	seeds.push(1490063483);
	seeds.push(919584127);
	seeds.push(-1134391393);
	seeds.push(1857626733);
	seeds.push(105332797);
	seeds.push(1140155976);
	seeds.push(-824920843);
	seeds.push(-1183376736);
	seeds.push(1867357304);
	seeds.push(1794779737);
	seeds.push(437586278);
	seeds.push(-2069970009);
	seeds.push(1624626473);
	seeds.push(584185992);
	seeds.push(-759103745);
	seeds.push(1691648113);
	seeds.push(1063421684);
	seeds.push(70452484);
	seeds.push(663927152);
	seeds.push(-1166330377);
	seeds.push(-773257492);
	seeds.push(-1932169399);
	seeds.push(-1716473519);
	seeds.push(-1787783272);
	seeds.push(-32549353);
	seeds.push(-1365875958);
	seeds.push(-279543652);
	seeds.push(-881472061);
	seeds.push(-2041961745);
	seeds.push(-1738573662);
	seeds.push(-1632880291);
	seeds.push(1035872950);
	seeds.push(-2072429091);
	seeds.push(1179790969);
	seeds.push(1993200207);
	seeds.push(2039882825);
	seeds.push(366315205);
	seeds.push(1896840460);
	seeds.push(2069056178);
	seeds.push(-874698811);
	seeds.push(-1347163381);
	seeds.push(1844400750);
	seeds.push(-680410431);
	seeds.push(2098218813);
	seeds.push(208334067);
	seeds.push(1637807533);
	seeds.push(-666473445);
	seeds.push(954716554);
	seeds.push(1755678025);
	seeds.push(1062308381);
	seeds.push(-1809681698);
	seeds.push(-1309646014);
	seeds.push(-1436663457);
	seeds.push(-379716446);
	seeds.push(-355083091);
	seeds.push(-1317773029);
	seeds.push(1618547924);
	seeds.push(689958362);
	seeds.push(-1716570503);
	seeds.push(229036137);
	seeds.push(559309028);
	seeds.push(1774331732);
	seeds.push(1834222875);
	seeds.push(-1430841167);
	seeds.push(1956890457);
	seeds.push(1603876363);
	seeds.push(1371682328);
	seeds.push(-311809403);
	seeds.push(150784341);
	seeds.push(-1940512826);
	seeds.push(586810366);
	seeds.push(2142620039);
	seeds.push(-160789721);
	seeds.push(14127794);
	seeds.push(362314117);
	seeds.push(2056940818);
	seeds.push(2009461511);
	seeds.push(135404279);
	seeds.push(-424557670);
	seeds.push(-1262593062);
	seeds.push(1208363310);
	seeds.push(-1148112451);
	seeds.push(1973336127);
	seeds.push(-422634322);
	seeds.push(-1387684881);
	seeds.push(808791126);
	seeds.push(30849653);
	seeds.push(1106421276);
	seeds.push(-441967107);
	seeds.push(-909971522);
	seeds.push(-30225755);
	seeds.push(655880863);
	seeds.push(-1290499361);
	seeds.push(-607810536);
	seeds.push(-542189677);
	seeds.push(851343779);
	seeds.push(1127501608);
	seeds.push(-2064168506);
	seeds.push(-796605625);
	seeds.push(704741944);
	seeds.push(1975874988);
	seeds.push(-1532456846);
	seeds.push(677279489);
	seeds.push(713839143);
	seeds.push(1586587962);
	seeds.push(-836085701);
	seeds.push(977978954);
	seeds.push(-312800992);
	seeds.push(-707135317);
	seeds.push(1046941509);
	seeds.push(1277614179);
	seeds.push(-857660652);
	seeds.push(261069042);
	seeds.push(-575635712);
	seeds.push(-1466715400);
	seeds.push(-1689757016);
	seeds.push(1887721458);
	seeds.push(-836817995);
	seeds.push(317858490);
	seeds.push(-542371088);
	seeds.push(-11267845);
	seeds.push(569184807);
	seeds.push(2044594117);
	seeds.push(-2047866122);
	seeds.push(347617777);
	seeds.push(1933675386);
	seeds.push(1408613057);
	seeds.push(-1584892071);
	seeds.push(-433590724);
	seeds.push(1006571774);
	seeds.push(-1682693139);
	seeds.push(1364369782);
	seeds.push(-583541585);
	seeds.push(-55337288);
	seeds.push(-1125680099);
	seeds.push(-249462065);
	seeds.push(15781446);
	seeds.push(1922328966);
	seeds.push(-199379223);
	seeds.push(575423562);
	seeds.push(2116464208);
	seeds.push(-1908050);
	seeds.push(-888179894);
	seeds.push(778344836);
	seeds.push(1148278482);
	seeds.push(1353147661);
	seeds.push(-529027663);
	seeds.push(1300316871);
	seeds.push(1723113354);
	seeds.push(-1058478439);
	seeds.push(497837376);
	seeds.push(-668616547);
	seeds.push(-956115080);
	seeds.push(-1225033910);
	seeds.push(732938302);
	seeds.push(-1105736405);
	seeds.push(-1546189709);
	seeds.push(-202356097);
	seeds.push(-329828626);
	seeds.push(714545037);
	seeds.push(-1953629767);
	seeds.push(-297971201);
	seeds.push(-1569248681);
	seeds.push(1541366073);
	seeds.push(-1383083673);
	seeds.push(214167167);
	seeds.push(-355018844);
	seeds.push(1662521257);
	seeds.push(604279994);
	seeds.push(-1665289534);
	seeds.push(982389749);
	seeds.push(155893620);
	seeds.push(-1385031116);
	seeds.push(-526188325);
	seeds.push(514261031);
	seeds.push(-1960245754);
	seeds.push(1213075726);
	seeds.push(-1849016888);
	seeds.push(-1487315804);
	seeds.push(-1716120282);
	seeds.push(-1758426467);
	seeds.push(1825501584);
	seeds.push(-2134985813);
	seeds.push(279511387);
	seeds.push(3053537);
	seeds.push(-1022559711);
	seeds.push(-786364969);
	seeds.push(1218795937);
	seeds.push(-583349649);
	seeds.push(1545164275);
	seeds.push(-1189808104);
	seeds.push(-111451678);
	seeds.push(213697111);
	seeds.push(1520714868);
	seeds.push(-1713474703);
	seeds.push(727690245);
	seeds.push(-697347852);
	seeds.push(-1622192981);
	seeds.push(-856918401);
	seeds.push(378723343);
	seeds.push(-1608424352);
	seeds.push(115346486);
	seeds.push(-1337362572);
	seeds.push(-865994974);
	seeds.push(1803922377);
	seeds.push(-328229502);
	seeds.push(-930584948);
	seeds.push(-534456994);
	seeds.push(-1256986380);
	seeds.push(240067451);
	seeds.push(-1306322339);
	seeds.push(-1741591665);
	seeds.push(1718848962);
	seeds.push(17760905);
	seeds.push(-958348367);
	seeds.push(1712146287);
	seeds.push(-470848116);
	seeds.push(-1292800811);
	seeds.push(-1987616217);
	seeds.push(-1285466457);
	seeds.push(1668730207);
	seeds.push(-362750119);
	seeds.push(-985135736);
	seeds.push(-776538776);
	seeds.push(559707142);
	seeds.push(1849469669);
	seeds.push(1917159922);
	seeds.push(109990850);
	seeds.push(601187808);
	seeds.push(-177013068);
	seeds.push(1773649039);
	seeds.push(-156925728);
	seeds.push(-2001633122);
	seeds.push(1548540035);
	seeds.push(965625902);
	seeds.push(1540697477);
	seeds.push(-607845015);
	seeds.push(-862130391);
	seeds.push(1159496211);
	seeds.push(751480434);
	seeds.push(1107757932);
	seeds.push(57977246);
	seeds.push(1561626543);
	seeds.push(725979278);
	seeds.push(9321924);
	seeds.push(103789522);
	seeds.push(-964370792);
	seeds.push(716233334);
	seeds.push(2025890954);
	seeds.push(1080232185);
	seeds.push(-664489581);
	seeds.push(1147091856);
	seeds.push(1996929413);
	seeds.push(-1971414377);
	seeds.push(1147828333);
	seeds.push(-1104899585);
	seeds.push(1571685886);
	seeds.push(1062759363);
	seeds.push(713122779);
	seeds.push(-1248157602);
	seeds.push(90016427);
	seeds.push(212051453);
	seeds.push(1062527528);
	seeds.push(570042771);
	seeds.push(1372144968);
	seeds.push(803891447);
	seeds.push(515831406);
	seeds.push(-870519142);
	seeds.push(-1083518259);
	seeds.push(-1104914331);
	seeds.push(162455665);
	seeds.push(515483156);
	seeds.push(1202402030);
	seeds.push(1889069173);
	seeds.push(129866114);
	seeds.push(1685606383);
	seeds.push(-656193480);
	seeds.push(665523608);
	seeds.push(1606302695);
	seeds.push(2111664358);
	seeds.push(744516513);
	seeds.push(1183660039);
	seeds.push(892957035);
	seeds.push(1471870788);
	seeds.push(602739640);
	seeds.push(-1145850775);
	seeds.push(-477938107);
	seeds.push(1715761386);
	seeds.push(-1953122114);
	seeds.push(-1258402676);
	seeds.push(-711688740);
	seeds.push(-951166350);
	seeds.push(-2128898196);
	seeds.push(814452011);
	seeds.push(-1137506915);
	seeds.push(1431123828);
	seeds.push(620009555);
	seeds.push(1904693744);
	seeds.push(720091937);
	seeds.push(597027356);
	seeds.push(566540662);
	seeds.push(-1847664575);
	seeds.push(1797641984);
	seeds.push(-336582836);
	seeds.push(-466580407);
	seeds.push(1149671037);
	seeds.push(353409539);
	seeds.push(1625436966);
	seeds.push(-712122169);
	seeds.push(343248233);
	seeds.push(1605208650);
	seeds.push(994526151);
	seeds.push(1176155153);
	seeds.push(-572474814);
	seeds.push(991804746);
	seeds.push(-100184042);
	seeds.push(-349232641);
	seeds.push(-2038658499);
	seeds.push(867774854);
	seeds.push(635724695);
	seeds.push(1380622259);
	seeds.push(-848911117);
	seeds.push(-853085807);
	seeds.push(244743492);
	seeds.push(2136162253);
	seeds.push(578008215);
	seeds.push(223831070);
	seeds.push(-1803849312);
	seeds.push(1329342610);
	seeds.push(1769339243);
	seeds.push(1919286661);
	seeds.push(-869223447);
	seeds.push(-767689144);
	seeds.push(1600949930);
	seeds.push(246467103);
	seeds.push(-683563891);
	seeds.push(-29207509);
	seeds.push(283562231);
	seeds.push(-2015853786);
	seeds.push(-2077458509);
	seeds.push(-2083025733);
	seeds.push(1501000884);
	seeds.push(1453654468);
	seeds.push(370120109);
	seeds.push(421597907);
	seeds.push(1218013355);
	seeds.push(86222538);
	seeds.push(1897585315);
	seeds.push(-982115692);
	seeds.push(937807109);
	seeds.push(466885654);
	seeds.push(-778357638);
	seeds.push(-1769062039);
	seeds.push(749867090);
	seeds.push(278106464);
	seeds.push(1154251957);
	seeds.push(1671417434);
	seeds.push(-586477980);
	seeds.push(-44660172);
	seeds.push(43169167);
	seeds.push(1107083242);
	seeds.push(725117195);
	seeds.push(-1354009211);
	seeds.push(-1025075771);
	seeds.push(1431479916);
	seeds.push(-1467550012);
	seeds.push(1492755608);
	seeds.push(1964129656);
	seeds.push(-61737248);
	seeds.push(2099185788);
	seeds.push(-322760675);
	seeds.push(-1916356592);
	seeds.push(395413118);
	seeds.push(728267877);
	seeds.push(-1637218482);
	seeds.push(931327883);
	seeds.push(1670499906);
	seeds.push(1794843145);
	seeds.push(-532924756);
	seeds.push(-833011027);
	seeds.push(585464688);
	seeds.push(-1095082900);
	seeds.push(1639971996);
	seeds.push(-1363250881);
	seeds.push(1077804427);
	seeds.push(-487251049);
	seeds.push(15414769);
	seeds.push(29229850);
	seeds.push(2006937346);
	seeds.push(-366425801);
	seeds.push(-255663120);
	seeds.push(-110606817);
	seeds.push(432373534);
	seeds.push(-479192449);
	seeds.push(916349699);
	seeds.push(-1842738400);
	seeds.push(-2146198500);
	seeds.push(-736813663);
	seeds.push(1628632888);
	seeds.push(-1762331686);
	seeds.push(670054845);
	seeds.push(-771965701);
	seeds.push(-1221603033);
	seeds.push(-1474736601);
	seeds.push(-700585423);
	seeds.push(-1643459055);
	seeds.push(2129414907);
	seeds.push(645274618);
	seeds.push(-1307259432);
	seeds.push(-59427572);
	seeds.push(-1078093163);
	seeds.push(407561438);
	seeds.push(538823141);
	seeds.push(-940368581);
	seeds.push(-1977815879);
	seeds.push(-1946355804);
	seeds.push(-289262661);
	seeds.push(-767233503);
	seeds.push(620885354);
	seeds.push(-965808998);
	seeds.push(-220357793);
	seeds.push(1227814957);
	seeds.push(-1959600017);
	seeds.push(819446706);
	seeds.push(-852429037);
	seeds.push(401764892);
	seeds.push(1378408397);
	seeds.push(-1064312967);
	seeds.push(-661843956);
	seeds.push(-1728912165);
	seeds.push(-1382992479);
	seeds.push(-951804938);
	seeds.push(-840757974);
	seeds.push(785941937);
	seeds.push(-1295900997);
	seeds.push(-679633898);
	seeds.push(-128951698);
	seeds.push(-820666306);
	seeds.push(-927256088);
	seeds.push(1780862578);
	seeds.push(-615931830);
	seeds.push(1498735042);
	seeds.push(1786596278);
	seeds.push(230954785);
	seeds.push(2092924402);
	seeds.push(985816549);
	seeds.push(1642830629);
	seeds.push(1346729736);
	seeds.push(-1944152235);
	seeds.push(982650775);
	seeds.push(1836702996);
	seeds.push(1708419755);
	seeds.push(-1959475944);
	seeds.push(1437896843);
	seeds.push(1505117461);
	seeds.push(236677699);
	seeds.push(-1237192318);
	seeds.push(-1619978306);
	seeds.push(111502162);
	seeds.push(337744126);
	seeds.push(-672161933);
	seeds.push(691963196);
	seeds.push(1445105272);
	seeds.push(-1777190374);
	seeds.push(-1379137200);
	seeds.push(921519774);
	seeds.push(-1724936607);
	seeds.push(-1522313432);
	seeds.push(-1070173957);
	seeds.push(66305007);
	seeds.push(1253455330);
	seeds.push(-2063568806);
	seeds.push(-549477828);
	seeds.push(288287729);
	seeds.push(-824440691);
	seeds.push(673691371);
	seeds.push(487673292);
	seeds.push(-1960022926);
	seeds.push(-285317318);
	seeds.push(-1429332510);
	seeds.push(808646844);
	seeds.push(120326322);
	seeds.push(1793393299);
	seeds.push(-1777757391);
	seeds.push(420412061);
	seeds.push(-2131885944);
	seeds.push(-825042593);
	seeds.push(-439406109);
	seeds.push(-883430616);
	seeds.push(-1409423165);
	seeds.push(1248192092);
	seeds.push(-2066831582);
	seeds.push(-1068685684);
	seeds.push(-1783594970);
	seeds.push(1350337049);
	seeds.push(-2001790504);
	seeds.push(-2059605182);
	seeds.push(1036763193);
	seeds.push(-794397284);
	seeds.push(1099583494);
	seeds.push(2061364618);
	seeds.push(-423234294);
	seeds.push(781643330);
	seeds.push(299944069);
	seeds.push(1712692512);
	seeds.push(-1734186309);
	seeds.push(2038078258);
	seeds.push(-1550560272);
	seeds.push(1308334768);
	seeds.push(1993156709);
	seeds.push(-1462037336);
	seeds.push(1938981057);
	seeds.push(-249340222);
	seeds.push(2074618531);
	seeds.push(-1834346943);
	seeds.push(1110193968);
	seeds.push(-1589636048);
	seeds.push(-447042316);
	seeds.push(-407942009);
	seeds.push(-625914262);
	seeds.push(1443824823);
	seeds.push(-2099024050);
	seeds.push(-1145113894);
	seeds.push(-97308344);
	seeds.push(1987369914);
	seeds.push(1315858705);
	seeds.push(2059961768);
	seeds.push(-2111363975);
	seeds.push(-1581866561);
	seeds.push(-2084439489);
	seeds.push(776839054);
	seeds.push(-368076554);
	seeds.push(-1111200625);
	seeds.push(1862451701);
	seeds.push(-713757072);
	seeds.push(-680311284);
	seeds.push(1539484153);
	seeds.push(1635714861);
	seeds.push(-673874006);
	seeds.push(-2090229933);
	seeds.push(-1791823834);
	seeds.push(851493797);
	seeds.push(-1997976766);
	seeds.push(-639951970);
	seeds.push(1313000914);
	seeds.push(-1176544008);
	seeds.push(-1214710189);
	seeds.push(-500260288);
	seeds.push(1782492018);
	seeds.push(1772065347);
	seeds.push(-1812041038);
	seeds.push(-1932931723);
	seeds.push(-455489270);
	seeds.push(-1794587384);
	seeds.push(-1079019225);
	seeds.push(-2055953282);
	seeds.push(49633186);
	seeds.push(1931772625);
	seeds.push(-434314047);
	seeds.push(-76143094);
	seeds.push(-1941457539);
	seeds.push(1737616341);
	seeds.push(-1006793863);
	seeds.push(876047994);
	seeds.push(-359421901);
	seeds.push(-1298532886);
	seeds.push(-842944597);
	seeds.push(-1761698491);
	seeds.push(-1327613229);
	seeds.push(1311701750);
	seeds.push(-983526589);
	seeds.push(356530898);
	seeds.push(262487304);
	seeds.push(-475804559);
	seeds.push(-34830182);
	seeds.push(348260972);
	seeds.push(747501506);
	seeds.push(-1873595573);
	seeds.push(1537227664);
	seeds.push(571072099);
	seeds.push(359378428);
	seeds.push(1975902895);
	seeds.push(-453994759);
	seeds.push(1738164023);
	seeds.push(880599074);
	seeds.push(-348498637);
	seeds.push(818593662);
	seeds.push(176325582);
	seeds.push(1764650383);
	seeds.push(725131581);
	seeds.push(-704137221);
	seeds.push(-722714689);
	seeds.push(-1150115706);
	seeds.push(-1635882877);
	seeds.push(-923550040);
	seeds.push(314054616);
	seeds.push(935269075);
	seeds.push(-2128966367);
	seeds.push(-584561);
	seeds.push(863504930);
	seeds.push(-134146948);
	seeds.push(-1209034932);
	seeds.push(1116631734);
	seeds.push(-310436532);
	seeds.push(1041444372);
	seeds.push(2114593194);
	seeds.push(2052922633);
	seeds.push(2089669946);
	seeds.push(87409037);
	seeds.push(-461027066);
	seeds.push(950782755);
	seeds.push(-17224327);
	seeds.push(-1315890024);
	seeds.push(142716680);
	seeds.push(-1104607410);
	seeds.push(1282435631);
	seeds.push(1540674185);
	seeds.push(-907842038);
	seeds.push(1037241243);
	seeds.push(-1610409590);
	seeds.push(1696366837);
	seeds.push(27943883);
	seeds.push(553171559);
	seeds.push(-581580772);
	seeds.push(1906107570);
	seeds.push(-289473074);
	seeds.push(820580325);
	seeds.push(-1419671664);
	seeds.push(-663599750);
	seeds.push(2009438013);
	seeds.push(76090277);
	seeds.push(280019408);
	seeds.push(2061782285);
	seeds.push(-437492744);
	seeds.push(-1312904691);
	seeds.push(402083758);
	seeds.push(309878338);
	seeds.push(-926394757);
	seeds.push(486597011);
	seeds.push(-131792581);
	seeds.push(1427338961);
	seeds.push(-536139256);
	seeds.push(-1237894801);
	seeds.push(281960866);
	seeds.push(-506590530);
	seeds.push(-1175529815);
	seeds.push(-770715141);
	seeds.push(-1444210505);
	seeds.push(-381714264);
	seeds.push(588021709);
	seeds.push(-1338659886);
	seeds.push(-466750198);
	seeds.push(-853043470);
	seeds.push(1858353553);
	seeds.push(-1408260457);
	seeds.push(1331034204);
	seeds.push(-1005723971);
	seeds.push(2017721899);
	seeds.push(165576223);
	seeds.push(1929056326);
	seeds.push(1546695024);
	seeds.push(-464683700);
	seeds.push(-1763313949);
	seeds.push(1309156993);
	seeds.push(-816286387);
	seeds.push(914224514);
	seeds.push(-359844206);
	seeds.push(-1366848857);
	seeds.push(1905420674);
	seeds.push(719051383);
	seeds.push(1880590195);
	seeds.push(-2043032072);
	seeds.push(873264807);
	seeds.push(1225488000);
	seeds.push(-1480462609);
	seeds.push(529471573);
	seeds.push(-1007035358);
	seeds.push(1481321341);
	seeds.push(255598402);
	seeds.push(1818105186);
	seeds.push(-1776670733);
	seeds.push(-460511335);
	seeds.push(-1650436236);
	seeds.push(-1485408311);
	seeds.push(1169646684);
	seeds.push(-1896309072);
	seeds.push(-264427027);
	seeds.push(13362234);
	seeds.push(213942577);
	seeds.push(1638191566);
	seeds.push(-985602433);
	seeds.push(-1636957260);
	seeds.push(2142711241);
	seeds.push(1428618194);
	seeds.push(-1025873851);
	seeds.push(-24430884);
	seeds.push(1605660157);
	seeds.push(2052999542);
	seeds.push(447163409);
	seeds.push(328632343);
	seeds.push(-1972997474);
	seeds.push(1118970897);
	seeds.push(392061918);
	seeds.push(1940253147);
	seeds.push(-453525028);
	seeds.push(456099836);
	seeds.push(2135703047);
	seeds.push(-790675544);
	seeds.push(758180335);
	seeds.push(97636137);
	seeds.push(-218105916);
	seeds.push(-1092003245);
	seeds.push(1654884214);
	seeds.push(1334701674);
	seeds.push(-1746639376);
	seeds.push(-2018043015);
	seeds.push(-660975881);
	seeds.push(98519576);
	seeds.push(-1051287887);
	seeds.push(-203167666);
	seeds.push(-1499282368);
	seeds.push(-484672094);
	seeds.push(214204302);
	seeds.push(1053220822);
	seeds.push(-288192227);
	seeds.push(350989668);
	seeds.push(1949739189);
	seeds.push(1657264945);
	seeds.push(1346728694);
	seeds.push(-978941241);
	seeds.push(1502829088);
	seeds.push(1815799155);
	seeds.push(-95469295);
	seeds.push(-1780453855);
	seeds.push(612896014);
	seeds.push(112542350);
	seeds.push(86605259);
	seeds.push(-645853384);
	seeds.push(-715248245);
	seeds.push(-1841479872);
	seeds.push(1482029479);
	seeds.push(-1216031492);
	seeds.push(-669088481);
	seeds.push(859561819);
	seeds.push(-347484391);
	seeds.push(121677352);
	seeds.push(-1838652244);
	seeds.push(-165686157);
	seeds.push(-761596067);
	seeds.push(325045126);
	seeds.push(637640702);
	seeds.push(2073930533);
	seeds.push(1005046416);
	seeds.push(-722541731);
	seeds.push(-1876469143);
	seeds.push(-700180911);
	seeds.push(-150176887);
	seeds.push(1539465224);
	seeds.push(1896007570);
	seeds.push(-1107438196);
	seeds.push(482826423);
	seeds.push(-40743082);
	seeds.push(-1342907584);
	seeds.push(1141294637);
	seeds.push(-933615973);
	seeds.push(-1719005768);
	seeds.push(1578423662);
	seeds.push(-758212043);
	seeds.push(793285310);
	seeds.push(941627169);
	seeds.push(988668740);
	seeds.push(-1276591458);
	seeds.push(629753429);
	seeds.push(-2022838598);
	seeds.push(669010198);
	seeds.push(2033201703);
	seeds.push(550082606);
	seeds.push(-678857911);
	seeds.push(-1746666194);
	seeds.push(-831138025);
	seeds.push(-401802850);
	seeds.push(224315771);
	seeds.push(1626895723);
	seeds.push(-1383847474);
	seeds.push(871036161);
	seeds.push(-1277176803);
	seeds.push(1135364312);
	seeds.push(-309395203);
	seeds.push(1284946115);
	seeds.push(525849789);
	seeds.push(1149384859);
	seeds.push(1015154961);
	seeds.push(346484483);
	seeds.push(278886422);
	seeds.push(-820533864);
	seeds.push(-652942417);
	seeds.push(-1671097844);
	seeds.push(198645897);
	seeds.push(-1629827745);
	seeds.push(1355945229);
	seeds.push(-728958173);
	seeds.push(1512201493);
	seeds.push(-2124662225);
	seeds.push(1364161860);
	seeds.push(275481286);
	seeds.push(-1224305441);
	seeds.push(-982920750);
	seeds.push(-240403267);
	seeds.push(557281770);
	seeds.push(1702787157);
	seeds.push(1513941005);
	seeds.push(1227406192);
	seeds.push(-2054025606);
	seeds.push(559223896);
	seeds.push(109727134);
	seeds.push(1365006953);
	seeds.push(-446083370);
	seeds.push(1520903545);
	seeds.push(-680722533);
	seeds.push(2003692617);
	seeds.push(759319512);
	seeds.push(-1787908570);
	seeds.push(-938312348);
	seeds.push(901373400);
	seeds.push(1549836383);
	seeds.push(425713761);
	seeds.push(1857157498);
	seeds.push(-1498794042);
	seeds.push(1777945672);
	seeds.push(840688501);
	seeds.push(716287511);
	seeds.push(-1626910798);
	seeds.push(-1314427397);
	seeds.push(1394496341);
	seeds.push(-1841751301);
	seeds.push(-550902772);
	seeds.push(326968471);
	seeds.push(-569278808);
	seeds.push(47196028);
	seeds.push(1131458249);
	seeds.push(-334120106);
	seeds.push(-975654805);
	seeds.push(-1670477271);
	seeds.push(-231277388);
	seeds.push(-1288083249);
	seeds.push(-354195031);
	seeds.push(69398171);
	seeds.push(-1483622177);
	seeds.push(1418083282);
	seeds.push(1528353876);
	seeds.push(1597058532);
	seeds.push(-1655569343);
	seeds.push(-1653857824);
	seeds.push(-1737645727);
	seeds.push(1625798644);
	seeds.push(-16036725);
	seeds.push(1991824062);
	seeds.push(387730377);
	seeds.push(1247922805);
	seeds.push(1115577541);
	seeds.push(1560012760);
	seeds.push(-1460010978);
	seeds.push(1185871878);
	seeds.push(-1615087988);
	seeds.push(1583051549);
	seeds.push(1431698392);
	seeds.push(-1790096974);
}