// siLib. Houdini Digital Assets and Tools For A Post-Softimage World
// Copyright (C) 2017 Andy Nicholas
// https://github.com/fxnut/siLib
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses.

#ifndef SILIB_STABLENOISE
#define SILIB_STABLENOISE


float silib_noise_amplitude_lookup(const float rough; const int _octaves)
{
    // Change octave range from 1-10 to 0-9 and clamp
    int octaves = _octaves-1;
    octaves = octaves>9?9:octaves;
    float lookup_A[] = { -0.036838249471398576, 0.30926471260474253, 0.53599236443431408, 0.70880629629059921, 0.85012578468205779, 0.97054090998464115, 1.0759591852396269, 1.1700374748295563, 1.2552081394922179, 1.3331768246314124 };
    float lookup_B[] = { 1.9050592545649705, 2.191849079095336, 2.4777870813382838, 2.7631733098750519, 3.0481499440277355, 3.3328005951166313, 3.6171804442512574, 3.9013286722926388, 4.1852745502886979, 4.4690407818979621 };
    float lookup_C[] = { 0.5375642351786647, 0.53756424221395704, 0.53756453903637158, 0.53756862582209597, 0.53759908280234636, 0.53775357238759403, 0.53835623053920911, 0.54030000064442907, 0.5457289816770502, 0.55927738785197634 };
    if(octaves <= 0) return lookup_C[0]; // Force to a flat profile (only 1 octave)
    return lookup_A[octaves] * pow(rough, lookup_B[octaves]) + lookup_C[octaves];
}


float silib_xnoise_amplitude_lookup(const float rough; const int _octaves)
{
    // Change octave range from 1-10 to 0-9 and clamp
    int octaves = _octaves-1;
    octaves = octaves>9?9:octaves;
    float lookup_A[] = { -0.06289675027148911, 0.30346180355473162, 0.59878615399031698, 0.85574891460576641, 1.0874978975924021, 1.3009516555316951, 1.5003019309058305, 1.6883241331928076, 1.8669724798723961, 2.0376867315707243 };
    float lookup_B[] = { 1.1291443182051717, 1.6407334224791605, 2.1081998088417011, 2.5491363046917885, 2.9713403580204085, 3.3791927096495984, 3.7754845061915079, 4.1621413306359365, 4.5405670498562394, 4.911827701439031 };
    float lookup_C[] = { 0.72837136725032503, 0.75537565634595261, 0.77713154649253613, 0.79605446477164232, 0.81311597467248553, 0.82882717299844444, 0.84349764690368534, 0.85733233989266855, 0.87047553364732588, 0.88303351240832595 };
    if(octaves <= 0) return lookup_C[0]; // Force to a flat profile (only 1 octave)
    return lookup_A[octaves] * pow(rough, lookup_B[octaves]) + lookup_C[octaves];
}


float silib_onoise_amplitude_lookup(const float rough; const int _octaves)
{
    // Change octave range from 1-10 to 0-9 and clamp
    int octaves = _octaves-1;
    octaves = octaves>9?9:octaves;
    float lookup_A[] = { 0.039325716053763893, 0.35147647559605177, 0.59744580205908837, 0.8083656994259264, 0.99654556197661426, 1.1683863984575091, 1.3277312691688592, 1.4771059041845374, 1.6182775797330082, 1.7525412466045474 };
    float lookup_B[] = { 2.351239855298048, 2.385613884464894, 2.4564715504140664, 2.5708986818124657, 2.7346878005344561, 2.9528396004108952, 3.2298061595040988, 3.569631066703868, 3.9760388682011438, 4.4524962531747017 };
    float lookup_C[] = { 0.70017698394800487, 0.70034958691461924, 0.70088195981148671, 0.7020138640524437, 0.70400835028157749, 0.70714712484415365, 0.71172766267819898, 0.71806120348013025, 0.72647126580893318, 0.73729249421611487 };
    if(octaves <= 0) return lookup_C[0]; // Force to a flat profile (only 1 octave)
    return lookup_A[octaves] * pow(rough, lookup_B[octaves]) + lookup_C[octaves];
}


float silib_snoise_amplitude_lookup(const float rough; const int _octaves)
{
    // Change octave range from 1-10 to 0-9 and clamp
    int octaves = _octaves-1;
    octaves = octaves>9?9:octaves;
    float lookup_A[] = { 0.022864824849056831, 0.5288266993220887, 0.92550580323014708, 1.2645600407529862, 1.5663348549919669, 1.8413822428172359, 2.0960246632758937, 2.3344105117135698, 2.5594384120183284, 2.7732297264438839 };
    float lookup_B[] = { 3.6767910016312881, 4.006430954071722, 4.3360709065121563, 4.6657108589525906, 4.9953508113930249, 5.3249907638334593, 5.6546307162738927, 5.984270668714327, 6.3139106211547613, 6.6435505735951956 };
    float lookup_C[] = { 1.4098950264138623, 1.4098938548838233, 1.4098931683493394, 1.4098926806924275, 1.4098923021199419, 1.4098919925983477, 1.4098917307574022, 1.409891503833629, 1.4098913035903213, 1.4098911244011429 };
    if(octaves <= 0) return lookup_C[0]; // Force to a flat profile (only 1 octave)
    return lookup_A[octaves] * pow(rough, lookup_B[octaves]) + lookup_C[octaves];
}


float silib_anoise_amplitude_lookup(const float rough; const int _octaves)
{
    // Change octave range from 1-10 to 0-9 and clamp
    int octaves = _octaves-1;
    octaves = octaves>9?9:octaves;
    float lookup_A[] = { -0.12179450909596934, 0.21137808857260021, 0.48302378912170396, 0.72111614236541799, 0.93701141757921502, 1.1367210020929002, 1.3239036398140591, 1.5009908538594399, 1.6697001204452526, 1.8313002435890851 };
    float lookup_B[] = { 0.78562183448221368, 1.1140281509771746, 1.4705009718153701, 1.8465179439649275, 2.2377702082183508, 2.6416083232498115, 3.0562224368659505, 3.4802907122772986, 3.9128017202762937, 4.352954469502496 };
    float lookup_C[] = { 0.72093325206856373, 0.75071178660474025, 0.78097828537002578, 0.81156608832452481, 0.84239505382383761, 0.87341757553006916, 0.90460198912532486, 0.93592566798428578, 0.96737161675711159, 0.99892659121389804 };
    if(octaves <= 0) return lookup_C[0]; // Force to a flat profile (only 1 octave)
    return lookup_A[octaves] * pow(rough, lookup_B[octaves]) + lookup_C[octaves];
}


vector silib_noise_amplitude_lookup_3d(const float rough; const int _octaves)
{
    // Change octave range from 1-10 to 0-9 and clamp
    int octaves = _octaves-1;
    octaves = octaves>9?9:octaves;
    float lookup_A0[] = { -0.025271096695735018, 0.43205684667762245, 0.73026802967353621, 0.95690310017548041, 1.1418350682936453, 1.2991411471053893, 1.43665975930687, 1.5592358327412073, 1.6700879212574127, 1.7714705147133185 };
    float lookup_B0[] = { 2.0054025956958763, 2.1943338549241052, 2.4276461034117451, 2.6954360951748702, 2.9921819462756982, 3.3142500006804072, 3.6590240651540875, 4.024509199382587, 4.4091220172786478, 4.8115680025640923 };
    float lookup_C0[] = { 0.82788648314137991, 0.83277768884546577, 0.8382502053147336, 0.84413807167783717, 0.85035542288055699, 0.85684861503024734, 0.86358054940790496, 0.87052385585989045, 0.87765741139416154, 0.8849643627899505 };
    float lookup_A1[] = { 0.046134766240411906, 0.47236790861671984, 0.78536673160128334, 1.0419270883212981, 1.2633108075294626, 1.4601755423802651, 1.6387424361329379, 1.8030074148702635, 1.9557127085796959, 2.0988340810210362 };
    float lookup_B1[] = { 1.6183589142986898, 2.0417093404307849, 2.4603337892094084, 2.875918414663531, 3.2892571820479461, 3.7008149833464339, 4.1108976118508416, 4.5197216012820753, 4.9274483444141506, 5.334202771490391 };
    float lookup_C1[] = { 0.75380974670698075, 0.7620258674004956, 0.76991705046519854, 0.77760435794904759, 0.78514353782836888, 0.79256673805227573, 0.79989485724769993, 0.80714255204627949, 0.81432065790998098, 0.82143750301828078 };
    float lookup_A2[] = { 0.057409857440687273, 0.40146544308207366, 0.69902717414640503, 0.96991840197105794, 1.2225613319339828, 1.461553630506351, 1.6897605814663437, 1.9091235186886006, 2.1210362891408057, 2.3265433400005544 };
    float lookup_B2[] = { 1.451863124600774, 1.7598869181172929, 2.1018364712190278, 2.4678658575879577, 2.8529111499674511, 3.2538216410474288, 3.6684252998353113, 4.0951238463677324, 4.5326865284169893, 4.9801332627990194 };
    float lookup_C2[] = { 0.76888214487784579, 0.78340136056829357, 0.79535893777100752, 0.80590743351364313, 0.81551839302868345, 0.82444273944969182, 0.8328338098009761, 0.84079384406229551, 0.84839525942982319, 0.85569168431289566 };
    if(octaves <= 0) return set(lookup_C0[0], lookup_C1[0], lookup_C2[0]); // Force to a flat profile (only 1 octave)
    return set(lookup_A0[octaves] * pow(rough, lookup_B0[octaves]) + lookup_C0[octaves], 
               lookup_A1[octaves] * pow(rough, lookup_B1[octaves]) + lookup_C1[octaves],
               lookup_A2[octaves] * pow(rough, lookup_B2[octaves]) + lookup_C2[octaves]);
}


vector silib_xnoise_amplitude_lookup_3d(const float rough; const int _octaves)
{
    // Change octave range from 1-10 to 0-9 and clamp
    int octaves = _octaves-1;
    octaves = octaves>9?9:octaves;
    float lookup_A0[] = { -0.12925752044296512, 0.43396967438645095, 0.83336620868706834, 1.153528795599307, 1.4252777509456114, 1.6637836658810117, 1.8777796909502364, 2.0728120505164127, 2.2526505698067774, 2.4199888937061691 };
    float lookup_B0[] = { 1.1381699800256682, 1.6579754803287505, 2.1438698326693122, 2.6089742567107517, 3.0592066688616626, 3.4979316345325948, 3.9273125815498404, 4.3488532540525231, 4.7636569526791632, 5.1725661097136895 };
    float lookup_C0[] = { 0.76800997232739687, 0.79830995996415999, 0.82385274834691335, 0.8467258836131456, 0.86779895020904363, 0.88754034555111394, 0.9062389913621135, 0.92408900636043978, 0.94122877729222698, 0.95776136278474022 };
    float lookup_A1[] = { -0.13666066360460771, 0.49337159017583421, 0.89254550756109463, 1.1904259382266487, 1.4302422070261533, 1.632063510068865, 1.8069381512394305, 1.9616321125471661, 2.1006050748326608, 2.2269597555320466 };
    float lookup_B1[] = { 1.1311329832029124, 1.5214873402118663, 1.9323285999714264, 2.3570664659979608, 2.7924463317515311, 3.2364991519737858, 3.6878966023427058, 4.1456784358995495, 4.6091162699983714, 5.0776376188295647 };
    float lookup_C1[] = { 0.78533602973579297, 0.81557090767321716, 0.84293079863281173, 0.86857634628703584, 0.89301813960686927, 0.91654158113074935, 0.93932780173126273, 0.96150136250367679, 0.98315283012478405, 1.004350815314679 };
    float lookup_A2[] = { -0.13457523387773129, 0.39986403648108881, 0.79600292018174112, 1.1226534314042551, 1.4057631456969841, 1.6584018315233116, 1.8882270729583022, 2.100172372073875, 2.2976320696271455, 2.4830572206238801 };
    float lookup_B2[] = { 1.0742104496896694, 1.64527042431203, 2.1725047969126958, 2.6731538494993701, 3.1549197168950696, 3.6221530735189664, 4.0776374867001497, 4.523299863450962, 4.9605490977081512, 5.3904577311416801 };
    float lookup_C2[] = { 0.77698439369612637, 0.81937436336206848, 0.85234522043804772, 0.88038321945959186, 0.9052444198628542, 0.92783581946408189, 0.94869914123071186, 0.96818890914657396, 0.98655229816605128, 1.0039698594460722 };
    if(octaves <= 0) return set(lookup_C0[0], lookup_C1[0], lookup_C2[0]); // Force to a flat profile (only 1 octave)
    return set(lookup_A0[octaves] * pow(rough, lookup_B0[octaves]) + lookup_C0[octaves], 
               lookup_A1[octaves] * pow(rough, lookup_B1[octaves]) + lookup_C1[octaves],
               lookup_A2[octaves] * pow(rough, lookup_B2[octaves]) + lookup_C2[octaves]);
}


vector silib_onoise_amplitude_lookup_3d(const float rough; const int _octaves)
{
    // Change octave range from 1-10 to 0-9 and clamp
    int octaves = _octaves-1;
    octaves = octaves>9?9:octaves;
    float lookup_A0[] = { 0.030605984772858363, 0.50888140643418378, 0.87793261855087645, 1.1901726858795529, 1.4659915247386188, 1.7158768326878511, 1.9460727073358297, 2.1606549361194292, 2.3624589356092951, 2.553551917880899 };
    float lookup_B0[] = { 2.0251290799884374, 2.2186172728560485, 2.4577213620870673, 2.7322831839016839, 3.0366357682872946, 3.3670486339755499, 3.720835118601002, 4.0959460734035593, 4.4907547678510618, 4.9039310218417125 };
    float lookup_C0[] = { 0.96970922428977446, 0.97977097601265295, 0.98913825381761167, 0.9980812427150203, 1.0067214226603556, 1.0151277133105887, 1.023344357858037, 1.0314020675520601, 1.0393233497938339, 1.0471253733454051 };
    float lookup_A1[] = { 0.025988619384225586, 0.66129230985571841, 1.075227829276229, 1.3896528253900771, 1.6461250822296929, 1.8642200171835812, 2.0548341153975995, 2.2247007694619247, 2.378292099588414, 2.5187400895756262 };
    float lookup_B1[] = { 1.9775109400559658, 2.0743127799823995, 2.2129667944806948, 2.3884711798906806, 2.5977072359940476, 2.8384556364748499, 3.1090181587595516, 3.4080334145335005, 3.7343739272045386, 4.087083158200647 };
    float lookup_C1[] = { 0.91089405636990395, 0.92297412877066365, 0.93424352584671366, 0.94501677144863983, 0.9554355039286393, 0.9655801658309433, 0.97550244024979305, 0.98523822709143738, 0.99481385146591539, 1.0042494043091843 };
    float lookup_A2[] = { 0.024295062475388041, 0.54584336549753265, 0.97414785802100223, 1.3512874023644303, 1.6944397288411688, 2.0127319847115497, 2.3117353068150432, 2.5951608705844951, 2.8656352436187853, 3.1251021885719812 };
    float lookup_B2[] = { 1.7241906954246382, 1.9559517310713692, 2.2480483446299235, 2.5878324881033254, 2.96814231498995, 3.3842141093141791, 3.8325893170116005, 4.3106125490100364, 4.8161639251205761, 5.3475015180691567 };
    float lookup_C2[] = { 0.90578927880912563, 0.91716678378250349, 0.92886136322948931, 0.94076673030387648, 0.95283133462822456, 0.96502437292276377, 0.97732526361492389, 0.98971924468333705, 1.0021951929654433, 1.0147444165046076 };
    if(octaves <= 0) return set(lookup_C0[0], lookup_C1[0], lookup_C2[0]); // Force to a flat profile (only 1 octave)
    return set(lookup_A0[octaves] * pow(rough, lookup_B0[octaves]) + lookup_C0[octaves], 
               lookup_A1[octaves] * pow(rough, lookup_B1[octaves]) + lookup_C1[octaves],
               lookup_A2[octaves] * pow(rough, lookup_B2[octaves]) + lookup_C2[octaves]);
}


vector silib_snoise_amplitude_lookup_3d(const float rough; const int _octaves)
{
    // Change octave range from 1-10 to 0-9 and clamp
    int octaves = _octaves-1;
    octaves = octaves>9?9:octaves;
    float lookup_A0[] = { 0.38841668274404806, 0.7332437778789167, 1.1179919304449559, 1.5311972826008269, 1.9669410518413661, 2.4215308471812818, 2.8924159671520173, 3.377716319769128, 3.8759820695136722, 4.3860572324524236 };
    float lookup_B0[] = { 2.7096195955022093, 2.8808887792465563, 3.1237396261762709, 3.4290831620896292, 3.7912951116636759, 4.2063944521012306, 4.671347572007285, 5.1837308740170638, 5.7415430156681833, 6.3430903794113576 };
    float lookup_C0[] = { 1.9901329016389393, 1.9901331597600944, 1.9901333106038537, 1.9901334175632579, 1.9901335004897407, 1.9901335682211858, 1.9901336254701756, 1.9901336750488217, 1.9901337187705153, 1.9901337578731433 };
    float lookup_A1[] = { 0.00091606386167830678, 0.75905309173875235, 1.3118425309108215, 1.7629064270589874, 2.1508228173116777, 2.4948579105481432, 2.8062261238907587, 3.0921140528299773, 3.3574439394522502, 3.6057562413285051 };
    float lookup_B1[] = { 2.1766428406638898, 2.5200031942613421, 2.7979897527968607, 3.0405400688742468, 3.2597417330643128, 3.4619697792307367, 3.6510933491930802, 3.8296778799024724, 3.9995319076209888, 4.1619892489698973 };
    float lookup_C1[] = { 2.2426411536308861, 2.2426412783504124, 2.2426413515973151, 2.2426414036973688, 2.2426414441841014, 2.2426414773127568, 2.242641505356771, 2.2426415296749114, 2.2426415511445534, 2.2426415703653215 };
    float lookup_A2[] = { 0.098089538768647344, 0.92156593663383291, 1.4208375079820001, 1.7831814696051218, 2.0689637305063968, 2.3055766981262771, 2.5078402148660359, 2.6847025436540868, 2.8419917390937961, 2.9837207494928251 };
    float lookup_B2[] = { 1.6656576636284535, 1.8555573741695524, 2.0465745237922821, 2.2383209777152602, 2.4306115692743897, 2.6233369017537647, 2.8164245176354119, 3.0098228182490709, 3.2034931596748955, 3.3974055035695887 };
    float lookup_C2[] = { 2.0552616543454629, 2.0552623066144347, 2.0552626886204299, 2.0552629598610337, 2.0552631703677302, 2.0552633424395834, 2.0552634879771565, 2.0552636140867251, 2.0552637253534538, 2.0552638249089314 };
    if(octaves <= 0) return set(lookup_C0[0], lookup_C1[0], lookup_C2[0]); // Force to a flat profile (only 1 octave)
    return set(lookup_A0[octaves] * pow(rough, lookup_B0[octaves]) + lookup_C0[octaves], 
               lookup_A1[octaves] * pow(rough, lookup_B1[octaves]) + lookup_C1[octaves],
               lookup_A2[octaves] * pow(rough, lookup_B2[octaves]) + lookup_C2[octaves]);
}


vector silib_anoise_amplitude_lookup_3d(const float rough; const int _octaves)
{
    // Change octave range from 1-10 to 0-9 and clamp
    int octaves = _octaves-1;
    octaves = octaves>9?9:octaves;
    float lookup_A0[] = { -0.14603992613170957, 0.51133565693583449, 0.97530856030193691, 1.3461240433086243, 1.6601701019880211, 1.9353141521263573, 2.1818225971710139, 2.4062054761647693, 2.6128820344136803, 2.8050064193765158 };
    float lookup_B0[] = { 1.2238965727998756, 1.4385510036523512, 1.6857041856769008, 1.9566500582239199, 2.2467850708956787, 2.5531894794356731, 2.8738203426121114, 3.2071559493994606, 3.5520123309394132, 3.9074381432790606 };
    float lookup_C0[] = { 0.83711066492297848, 0.87519025695393182, 0.90847188040639049, 0.93897633813374026, 0.96756916990302733, 0.99472547361840413, 1.020742584799355, 1.0458226548949563, 1.0701112500303558, 1.0937177239102396 };
    float lookup_A1[] = { -0.15211788453658259, 0.33789120611559142, 0.75562158321574469, 1.132399009480292, 1.4813857127573504, 1.8097130647498068, 2.1217997321847348, 2.4206254151725917, 2.7083209487244377, 2.9864774867231634 };
    float lookup_B1[] = { 0.66232435000714696, 0.95495875465061375, 1.3296142102341819, 1.7699633633402378, 2.2666506816677039, 2.813401585661838, 3.4056312040900156, 4.0398007496673838, 4.7130723909702255, 5.4231051290952541 };
    float lookup_C1[] = { 0.88238840292571685, 0.89929049889367918, 0.92162608139522972, 0.94843152377874218, 0.97914132449956326, 1.0133698259639587, 1.0508315430715078, 1.0913037646731065, 1.1346062678644278, 1.1805892050290061 };
    float lookup_A2[] = { -0.25423079384261194, 0.31392728327945241, 0.79320411490785525, 1.2225737171357007, 1.6182794394635716, 1.9890737484210219, 2.3403568839012907, 2.6757579188667546, 2.9978644918247674, 3.3086039663453386 };
    float lookup_B2[] = { 0.74067748141710377, 1.2121717509636958, 1.6862743824115614, 2.1620788711323238, 2.6391528685703234, 3.1172409895099005, 3.5961741067911444, 4.0758317950326894, 4.5561238726290272, 5.0369802464220514 };
    float lookup_C2[] = { 0.76549927384519978, 0.82192846722373569, 0.87499136087221785, 0.92597995011128886, 0.97547961673891559, 1.0238242119172576, 1.0712289193028772, 1.1178436015810433, 1.1637783965079471, 1.2091175221649091 };
    if(octaves <= 0) return set(lookup_C0[0], lookup_C1[0], lookup_C2[0]); // Force to a flat profile (only 1 octave)
    return set(lookup_A0[octaves] * pow(rough, lookup_B0[octaves]) + lookup_C0[octaves], 
               lookup_A1[octaves] * pow(rough, lookup_B1[octaves]) + lookup_C1[octaves],
               lookup_A2[octaves] * pow(rough, lookup_B2[octaves]) + lookup_C2[octaves]);
}


float si_noisefv(vector pos; vector freq; vector offset; float rough; int octaves)
{  
    vector pp = pos * freq - offset;
    
    float nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (2*(float(noise(pp))-0.5));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    float amp_out = silib_noise_amplitude_lookup(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

vector si_noisevv(vector pos; vector freq; vector offset; float rough; int octaves)
{  
    vector pp = pos * freq - offset;
    
    vector nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (2*(vector(noise(pp))-0.5));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    vector amp_out = silib_noise_amplitude_lookup_3d(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

float si_noiseff(float pos; float freq; float offset; float rough; int octaves)
{  
    float pp = pos * freq - offset;
    
    float nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (2*(float(noise(pp))-0.5));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    float amp_out = silib_noise_amplitude_lookup(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

float si_noisefp(vector4 pos; vector4 freq; vector4 offset; float rough; int octaves)
{  
    vector4 pp = pos * freq - offset;
    
    float nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (2*(float(noise(pp))-0.5));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    float amp_out = silib_noise_amplitude_lookup(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

vector si_noisevf(float pos; float freq; float offset; float rough; int octaves)
{  
    float pp = pos * freq - offset;
    
    vector nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (2*(vector(noise(pp))-0.5));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    vector amp_out = silib_noise_amplitude_lookup_3d(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

vector si_noisevp(vector4 pos; vector4 freq; vector4 offset; float rough; int octaves)
{  
    vector4 pp = pos * freq - offset;
    
    vector nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (2*(vector(noise(pp))-0.5));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    vector amp_out = silib_noise_amplitude_lookup_3d(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

float si_xnoisefv(vector pos; vector freq; vector offset; float rough; int octaves)
{  
    vector pp = pos * freq - offset;
    
    float nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (2*(float(xnoise(pp))-0.5));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    float amp_out = silib_xnoise_amplitude_lookup(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

vector si_xnoisevv(vector pos; vector freq; vector offset; float rough; int octaves)
{  
    vector pp = pos * freq - offset;
    
    vector nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (2*(vector(xnoise(pp))-0.5));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    vector amp_out = silib_xnoise_amplitude_lookup_3d(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

float si_xnoiseff(float pos; float freq; float offset; float rough; int octaves)
{  
    float pp = pos * freq - offset;
    
    float nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (2*(float(xnoise(pp))-0.5));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    float amp_out = silib_xnoise_amplitude_lookup(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

float si_xnoisefp(vector4 pos; vector4 freq; vector4 offset; float rough; int octaves)
{  
    vector4 pp = pos * freq - offset;
    
    float nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (2*(float(xnoise(pp))-0.5));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    float amp_out = silib_xnoise_amplitude_lookup(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

vector si_xnoisevf(float pos; float freq; float offset; float rough; int octaves)
{  
    float pp = pos * freq - offset;
    
    vector nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (2*(vector(xnoise(pp))-0.5));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    vector amp_out = silib_xnoise_amplitude_lookup_3d(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

vector si_xnoisevp(vector4 pos; vector4 freq; vector4 offset; float rough; int octaves)
{  
    vector4 pp = pos * freq - offset;
    
    vector nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (2*(vector(xnoise(pp))-0.5));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    vector amp_out = silib_xnoise_amplitude_lookup_3d(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

float si_onoisefv(vector pos; vector freq; vector offset; float rough; int octaves)
{  
    vector pp = pos * freq - offset;
    
    float nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (float(onoise(pp)));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    float amp_out = silib_onoise_amplitude_lookup(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

vector si_onoisevv(vector pos; vector freq; vector offset; float rough; int octaves)
{  
    vector pp = pos * freq - offset;
    
    vector nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (vector(onoise(pp)));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    vector amp_out = silib_onoise_amplitude_lookup_3d(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

float si_snoisefv(vector pos; vector freq; vector offset; float rough; int octaves)
{  
    vector pp = pos * freq - offset;
    
    float nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (float(snoise(pp)));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    float amp_out = silib_snoise_amplitude_lookup(rough, octaves);
    nval = nval/amp_out;    
    float mulval = octaves*rough;
    nval += -0.005*mulval - 0.02;

    return nval;
}

vector si_snoisevv(vector pos; vector freq; vector offset; float rough; int octaves)
{  
    vector pp = pos * freq - offset;
    
    vector nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (vector(snoise(pp)));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    vector amp_out = silib_snoise_amplitude_lookup_3d(rough, octaves);
    nval = nval/amp_out;    
    float mulval = octaves*rough;
    float powval = rough*mulval;
    nval += set(0.0005*powval -0.0035*mulval - 0.015, 0.015 + 0.00525*mulval - 0.0007*powval, 0.0075 + 0.00475*mulval - 0.002*powval);

    return nval;
}

float si_anoisefv(vector pos; vector freq; vector offset; float rough; int octaves)
{  
    vector pp = pos * freq - offset;
    
    float nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (float(anoise(pp)));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    float amp_out = silib_anoise_amplitude_lookup(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

vector si_anoisevv(vector pos; vector freq; vector offset; float rough; int octaves)
{  
    vector pp = pos * freq - offset;
    
    vector nval=0.0;
    float local_amp=1.0;
    int cur_octave=0;
    while (cur_octave < octaves) 
    {
        nval += local_amp * (vector(anoise(pp)));
        local_amp *= rough;
        pp *= 2;
        cur_octave++;
    }

    vector amp_out = silib_anoise_amplitude_lookup_3d(rough, octaves);
    nval = nval/amp_out;    
    
    return nval;
}

#endif
