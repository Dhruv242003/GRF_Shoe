#include "ICM_20948.h"
#include<Wire.h>
#include <SD.h>
#include <SparkFun_MicroPressure.h>
#include "MicroFlow.h"

#define AD0_VAL 1  

int prev_time = 0;

float accX, accY, accZ, gyroX, gyroY, gyroZ;
float s1, s2, s3, s4, s = 0;

int topology[] = {13, 16, 16, 16, 16, 16, 16, 1};
double weights[] = {0.37744573, -1.975618, 0.34271008, 0.36747003, 0.22167443, 0.43038625, -0.31267166, -0.41646576, -1.3227768, 0.49677336, -0.1161232, -0.42988172, -0.16588292, 0.14681195, -0.044621557, -2.536467, -0.391296, 0.10750384, 0.033209443, -0.0241099, 0.5231453, 0.16819344, -0.15570402, 0.15094732, -0.015659206, -0.33716857, 0.15223545, 0.45578966, 0.100363046, 0.248147, 0.28430703, -0.067956716, -0.053975664, 0.0008686177, 0.08312839, -0.3165061, 0.47757366, -0.39588106, -0.28590804, 0.043262362, 0.445677, -0.28884894, -0.120381474, -0.10890532, 0.14704984, -0.033850867, -0.4352022, -0.3006125, -0.35928884, 0.3119569, -0.3293259, -0.26154083, 0.47302255, 0.12583975, -0.24285977, -0.22041328, 0.18132246, 0.6205009, -0.1902596, 0.3317355, 0.3145977, 0.1238346, 0.11108615, 0.3878982, 0.3378823, 0.14047259, -0.28860795, -0.1877662, -0.45228952, -0.06310246, 0.18077809, -0.33560473, -0.31519136, -0.24704343, -0.15806174, 0.1502041, -0.012650427, 0.29948828, -0.1105924, 0.37415233, -0.3978164, 0.20559138, 0.06292027, -0.35990143, 0.29314974, -0.05686634, -0.12487453, 0.13252476, 0.17631862, -0.14889689, -0.05089301, -0.33605283, 0.46988136, 0.42896667, -0.4334911, 0.29654628, 0.16995381, -0.35115334, -0.32162967, 0.15313774, -0.17933764, 0.19571239, -0.078693, -0.20972048, -0.38121837, -0.2654721, -0.3239782, 0.38261926, -0.3782034, 0.12796476, 0.29379496, 0.18960771, -0.09306376, 0.43770075, -0.09980196, -0.2630093, 0.58211815, -0.2945069, 0.27543294, -0.016554447, -0.0031139106, -0.13402528, 0.07747191, 0.011111191, -0.5092743, 0.4453265, 0.5820741, 0.07766105, -0.14005077, 0.4512747, -0.14540005, 0.17599678, -0.23469272, 0.017765863, -0.24836756, -0.44628546, 0.40333426, 0.01921699, 0.144876, 0.09305196, -0.67744637, -0.10684979, 0.43626404, -0.5866427, 0.026800666, 0.29916757, 0.17226917, 0.046866238, 0.6767545, -0.33278972, -0.38994628, 0.33057812, -0.18315996, 0.14101586, -0.19728771, -0.17671084, -0.13754323, -0.23283422, -0.070808604, 0.34785262, 0.25248903, -0.27736723, -0.108933836, 0.22227156, -0.41214195, 0.1516484, 0.4295249, 0.2816327, -0.492655, 0.4316985, 0.260395, 0.64328283, 0.34257618, -0.19171087, -0.21995562, -0.24781695, -0.34355012, -0.027048621, -0.35588464, -0.4182679, 0.055277944, 0.6039729, -0.16325116, -0.28908116, 0.046115164, -0.39426976, -0.26557937, -0.48301136, 0.39756757, 0.3674015, -0.35137293, -0.011315636, -0.3392198, -0.3017802, -0.009950429, -0.062057376, -0.27043104, 0.4650979, -0.28907764, -0.016802775, 0.36934823, 0.2276609, -0.013303161, -0.26526618, -0.38493043, 0.05849674, -0.33244878, 0.103962906, -0.22794335, -0.40367186, 0.3087168, 0.24374679, -0.37014207, 0.36171186, -0.3949833, 0.3039604, 0.07261309, 0.31329778, -0.26879075, 0.32043964, -0.103223085, 0.061571926, -0.10544285, 0.13033053, 0.09515075, -0.379843, -0.18909514, -0.83768755, 0.21341966, 0.8772677, -0.7942877, -0.033926457, -0.58557194, -0.11813254, -0.28694668, 0.8810744, -0.2318181, -0.24212162, 0.052500777, 0.32614154, 0.42012885, -0.18847334, 0.3354703, -0.15416539, -0.047388524, -0.4079807, -0.18275735, -0.026388526, 0.3243893, 0.04869625, 0.43033335, 0.27614513, -0.016862214, -0.3579499, -0.37196976, -0.36246246, 0.06343073, -0.22842872, 0.21646443, 0.08756462, -0.015222281, 0.065247506, 0.19235006, 0.08777359, 0.035092026, 0.32384184, -0.16356277, 0.34772268, 0.29258046, -0.1658464, 0.027330875, -0.09806934, 0.025897412, 0.2148455, 0.011321634, 0.5359521, -1.2813292, -0.07248107, 0.55467546, -0.31054288, -0.28408802, -0.029663898, -0.31797278, -0.40085465, 0.28322482, 0.04220197, 0.61985105, 0.2552107, 0.4261492, 0.23020874, 0.18813923, -0.4219767, 0.18303381, 0.39414778, 0.1624088, -0.08611569, 0.30653316, -0.01979711, 0.07131199, -0.31483185, -0.56254953, -0.06282224, -0.5588588, -0.15307777, 0.2770935, -0.41545114, 0.3990884, 0.15927693, -0.14864278, 0.12460527, 0.02037561, 0.1858168, 0.13622251, -0.20055883, 0.42376927, 0.40487346, 0.19663379, 0.41132542, 0.2512587, 0.3973669, 0.22818227, 0.28611815, 0.0010028481, 0.065302275, -0.36131352, 0.2583334, 0.039772652, 0.3705735, 0.2296357, -0.41139418, -0.19332212, -0.3813982, -0.3353888, 0.4124274, -0.2637721, 0.14740106, -0.26391703, -0.0637311, -0.10247648, 0.115096815, -0.76274425, 0.8027365, -0.08126488, 0.033398718, 0.25352076, -0.5306756, 0.19149281, 0.63994193, -0.22744367, -0.03315454, -0.35725203, 0.6216274, -0.59598297, 0.5992419, -0.23668116, -0.41410202, 0.5356434, -0.17821775, 0.18582202, -0.030225486, 0.28218594, 0.6849291, 0.3905747, 0.1462737, 0.2690141, 0.19427791, -0.2092341, -0.42732707, -0.4006888, -0.0016408563, 0.30780843, -0.16511351, 0.38491324, -0.25637293, -0.17989454, -0.2967834, -0.317793, -0.17103979, 0.122644395, -0.43167555, 0.0050283372, 0.20316061, 0.03563136, 0.16196176, 0.3332973, 0.44253787, -0.41446593, 0.37748307, -0.657039, 0.2294385, -0.24023648, -0.32839248, -0.2664046, 0.17583828, 0.19817202, 0.5178204, -0.114565894, -0.07371802, 0.39043, 0.2199449, 0.7703735, 0.9777068, -0.016144723, -0.11731876, -0.28625506, 0.7853486, -0.41040435, -0.42790982, -0.2468561, -0.30496466, -0.13160703, 0.7654438, -0.029093273, 0.24927463, -1.0453113, 0.48338056, 0.29851434, 0.021686437, -0.41647837, 0.049545817, 0.0983199, -0.12801117, 0.41966593, -0.38523898, 0.45349124, -0.03246142, -0.15330409, -0.12656188, -0.033150434, -0.29560763, -0.30152473, -0.14928705, -0.006501534, -0.18441962, -0.04549679, -0.054660168, -0.04820136, 0.6915045, -0.0052326624, -0.40682703, -0.6315302, -0.37137344, 0.07085167, 0.28184712, 0.6838676, -0.24922809, 0.26791406, 0.52576303, 0.2011752, 0.2995075, -0.0032186508, 0.99493426, 0.52531326, 0.38549525, 0.54284835, 0.33676502, -0.8820437, -0.65121996, -0.5063936, 0.19663882, 0.9273376, 0.109894656, 0.17586361, -0.56334263, 0.18667553, 0.3068146, -0.24142125, 0.23090601, 0.20967068, 0.4409226, 0.41188663, -0.13633722, -0.3783502, 0.23242849, -0.42429402, -0.102036, 0.009731233, 0.0045569884, -0.30046648, -0.29227063, 0.38650385, 0.14811403, 0.32653326, 0.06841128, 0.31737328, 0.37056208, 0.018523358, -0.030337354, -0.0089214975, -0.37205333, 0.12980948, -0.26038036, -0.189094, -0.43951273, 0.51776963, -0.14489342, -0.06378031, -0.13621238, -0.20333304, -0.0992668, -0.052333742, -0.1541431, -0.10020089, -0.13907063, -0.13199571, 0.08895847, -0.4129977, -0.3335427, 0.21441683, -0.1265952, 0.056735307, -0.21755101, -0.46276987, -0.2737155, 0.16238189, 0.14396282, 0.13200724, 0.032468367, -0.6518774, -0.076428026, 0.19213934, -0.08982578, -0.36625743, 0.22287399, -0.2849815, -0.0077564907, 0.47268617, 0.037853308, -0.19709836, 0.37425083, -0.094466835, 0.048118804, 0.10843161, -0.076065645, 0.6036783, -0.027498307, -0.25976348, -0.40898275, 1.6913424, 0.047465563, 0.120817035, 0.16639872, -0.3097558, -0.39418346, 0.14530832, 0.466355, 0.23981243, 0.35497168, 0.016384011, 0.36906803, -0.2971848, 0.17145221, 0.007177192, -0.105638616, 0.26158464, 0.12971492, -0.27767462, -0.52402455, -0.22877495, 0.37717947, 0.026416877, -0.07207956, 0.32332674, -0.46284068, 0.19486621, 0.25969395, -0.19143078, -0.24730901, -0.5520171, -0.3463238, -0.6549132, -0.6064103, -0.36243188, 0.20266911, 0.48325202, 0.29712692, 0.4025418, -0.30307215, -0.00069364905, 0.17429397, -0.24480891, 0.06571311, -0.0036757886, -0.36641628, 0.386241, -0.042579502, -0.05011505, 0.30893013, -0.33931768, -0.3724109, -0.1734179, 0.22401538, -0.23033392, -0.4208277, -0.39308873, -0.351434, 0.035066865, -0.089680694, 0.42955992, 0.12816007, 0.05676581, 0.1490138, 0.09478358, -0.9046956, -0.25336593, 0.43358147, 0.29861355, 0.35242763, -0.17685352, -0.0648064, 0.53949344, 0.80850923, -1.0974424, -0.6450039, -0.9254696, 0.22401479, 0.3258303, 0.22352138, -0.21563771, 0.30691835, 0.14385054, 0.014209706, -0.6717639, 0.04073033, 0.51687396, 0.21205164, 0.053434703, 0.098947935, 0.058152363, 0.2474677, -0.30534357, -0.17621432, 0.106893316, -0.24470313, -0.20489456, 0.10974929, -0.33786386, 0.06363944, 0.47149375, 0.36940798, 0.21118312, 0.3372803, 0.16348152, 0.73843837, -0.11192965, -0.2676442, 0.5450947, -0.5269318, 0.04933149, -0.39169404, 1.0010315, 0.44734585, -0.18713062, -0.07007569, 0.025696058, 0.061422236, -1.1707927, 0.9453924, -0.25896817, 0.45476273, -0.28595138, -0.74620676, 0.7870334, 0.4784686, 0.55555224, -0.3411699, 0.20786804, 0.8928466, -0.3785451, 0.8837963, -1.1266474, -1.4515709, -0.017074773, 0.32578397, -0.39241084, 0.07188192, 0.051522072, -0.26242232, -0.15241666, -0.2688852, 0.09012845, -0.13607484, 0.3823163, -0.062065598, -0.24075, 0.34828028, -0.30753094, -0.2038993, 0.42789644, -1.461187, 0.6326645, -0.2180716, -0.14151613, 0.76504767, 0.29317808, 0.2746202, 0.52560925, -0.3489255, 0.2688792, -0.15677525, -0.4211022, 0.3796758, -0.64337605, 0.31820816, 0.60428065, 0.7635516, 0.24783047, 1.2932074, -0.94702715, 0.7222486, 0.4705261, -0.24751152, -0.19975513, 0.16778395, -0.4132725, 0.5262189, -0.31320003, 0.6711057, -0.79294044, -0.052549075, -0.2766986, 0.012175849, -0.7378471, -0.12761097, -0.019622296, 0.6367653, 0.13951267, -0.14211792, 0.5947303, 0.2719509, -0.29754505, 0.055572085, 0.51872694, 0.2733946, -0.26446295, 0.17042644, 0.12146307, -1.3090088, 0.3188173, -0.24727875, -0.36630073, -0.09498196, -0.086714014, -0.2584919, -0.26521072, 0.21345669, 0.08239528, -0.048640575, 0.50638247, 0.20215158, 0.1276648, -1.1764394, 0.2576092, 0.13741107, -0.099884674, 0.360865, -0.33873892, -0.35361624, 0.42142728, -0.56407607, 0.34200814, 0.3085444, -0.10782048, -0.3648182, 0.25249562, -0.11373913, -0.6409077, -0.30692306, -0.23177736, -0.94991904, 0.44300744, -0.46065053, -0.18787435, 0.26018962, 0.28973147, 0.6043834, 0.043903187, 0.09481417, 0.49084005, 0.23008159, 0.0977139, -0.30732945, 0.49729708, -0.916627, -0.29000008, 0.4155359, 0.2200432, 0.020642413, -0.24890985, 0.047031313, -0.2928782, 0.16967845, 0.13587944, -0.15780959, 0.23314358, 0.28149077, 0.49418545, -0.4292927, -0.1659438, -0.18992993, -0.13165502, -0.055589564, -0.067707136, 0.23994942, -0.2647853, 0.028170912, -0.5221727, 0.122030586, 0.33051217, -0.36990115, -0.37928596, -0.0055585424, 0.5219413, 0.12449192, 0.16279379, 0.32973596, 0.15425688, -1.2659422, 0.37183094, 0.02589301, -0.06728575, 0.046837986, -0.41721335, 0.5709954, -0.25103256, -0.1342087, 0.64358974, 1.1798122, -0.42312753, -0.30008847, 0.7836674, -1.1309087, -0.09015748, -0.3329067, 0.36647165, -0.190862, 0.3797271, 0.18316337, -0.4297629, -0.49631906, -0.010398642, 0.58794135, -0.2991145, 0.42946216, -0.29676014, 0.1547476, 0.5671954, 0.36104846, -0.29423165, -0.20664176, -0.5935632, 0.38894662, 0.021783799, -0.18847775, -0.8079755, 0.11148809, 0.016988723, 0.18345188, -0.37429446, 0.5157463, 0.036478836, -0.3077982, 0.14195913, 0.14848791, -0.41444817, 0.30974206, -0.22315526, 0.35579595, 0.4138753, 0.23632465, -0.37465498, -0.28244507, -0.24418606, -0.30029547, -0.3874609, -0.34425864, -0.1059116, -0.025711617, 0.105716415, -0.40055174, 0.13343206, 1.7247021, -0.61231, -0.13985616, -0.040920347, -0.20300452, 0.66773534, -0.3995359, 0.3946514, -0.63937104, -2.2653098, -1.9772017, 0.66376203, 0.18115635, -0.5186848, 1.4468372, -0.455797, -0.29994673, -0.69673157, 0.12187382, -0.015515178, -0.923283, -0.18684234, -0.6229904, 0.4036448, -0.2684288, -1.4454534, -0.638851, -0.05285033, 0.06355887, -0.4143191, -0.12545139, 0.3943573, 0.1928756, -0.14331299, -0.19527148, 0.24209538, -0.3028154, 0.032272995, -0.40665132, -0.4151191, 0.09848717, 0.083170325, -0.41746575, 0.18357304, 0.061403334, -0.17898604, 0.100319415, -0.18554191, 0.72742224, -0.5160248, 0.18834756, 0.35068378, -0.41785103, 0.3679239, -0.2861159, -0.3804883, -0.20954937, -1.2357599, -0.52095056, 0.091491766, 0.30209622, 0.39687753, 0.67944753, -0.24242504, 0.26306984, -0.15627047, -0.27554336, -0.29027805, -0.5326936, 0.04487782, -0.088607125, 0.110791065, -0.251664, 0.35538092, 0.16274047, 0.46041882, -0.08840607, 0.074489936, 0.52229047, -0.2676533, 0.06749545, -0.21834478, -0.4532138, 0.40654382, -1.195049, -0.3463419, 0.0601418, 0.18495883, -0.285219, -0.44752657, -0.034678515, -0.22992934, -0.2593738, -0.25684002, 0.35418996, -0.31401157, 0.80265784, -0.5171602, -0.27458173, -0.30160555, -0.43954524, -0.8370899, -0.5091825, 0.068309925, -0.17601638, -1.0906916, -0.18014944, 0.31128782, -0.4565776, -0.5047798, 0.6576818};
double biases[] = {-0.016398966, -0.1159133, 0.0, 0.0, -0.00035698657, -0.15729229, 0.0, -0.0026061719, 0.050456237, 0.18308727, 0.0, -0.04166867, 0.080085166, -0.08525059, 0.20133582, -0.07090731, -0.09753101, -0.016535325, 0.0, 0.070504725, -0.089041434, -0.05656308, -0.00568247, 0.0, 0.13853216, -0.1349743, 0.019823767, 0.04516028, 0.0075938064, -0.028343549, -0.08955264, -0.10335885, 0.046775635, -0.0371664, -0.08606679, 0.02094636, 0.075214125, -0.033210773, 0.017462015, -0.052028697, -0.2960243, -0.015191593, 0.095562, -0.07043441, 0.0, -0.1325552, 0.090032555, -0.0106325885, -0.031438436, 0.06176706, 0.13765262, -0.14307632, 0.0, -0.16398881, 0.040267486, 0.0026020173, -0.07511298, -0.07429017, 0.03455117, -0.05724263, 0.10309279, -0.021617522, 0.05632395, 0.06202442, 0.115279905};
int layers = 8;


#define PCAADDR 0x70

SparkFun_MicroPressure mpr1; 
SparkFun_MicroPressure mpr2;
SparkFun_MicroPressure mpr3;
SparkFun_MicroPressure mpr4;

ICM_20948_I2C myICM; // Otherwise create an ICM_20948_I2C object  (9 DOF IMU object)

void pcaselect(uint8_t i) {
  if (i > 3) return;
 
  Wire.beginTransmission(PCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

// SD Card Config +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define FILE_BASE_NAME "DATA"  

File file;                                                                                          // Chip Select Pin
int cs_pin = 7;                                                                                    // initialize file name, plus a null terminator        
int count = 0;
char fileName[22] = FILE_BASE_NAME "00.csv";
float cTime;


int avg_size = 1000; 
static int baseline_value_1;
static int baseline_value_2;
static int baseline_value_3;
static int baseline_value_4;

int current_value_1;
int current_value_2;
int current_value_3;
int current_value_4;
int offset_value_1;
int offset_value_2;
int offset_value_3;
int offset_value_4;
float final_value_1, final_value_2, final_value_3, final_value_4;

MicroMLP mlp(layers, topology, weights, biases, RELU);
double grf;

void setup(){

  Wire.begin();
  Serial.begin(2000000);


   // Blink Portenta LED Yellow ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
  digitalWrite(LEDR,LOW);                                        
  digitalWrite(LEDG,LOW);                                        
  digitalWrite(LEDB,HIGH);  

  // Reading Average Baseline Pressure Values ---------------------------------------------------------------------------------------------------------------------------------------------------


  baseline_value_1 = 0;
  baseline_value_2 = 0;
  baseline_value_3 = 0;
  baseline_value_4 = 0;
  
  //Serial.println("Done averaging baseline values...");

  
  #ifdef USE_SPI
  SPI_PORT.begin();
#else
  Wire.begin();
  Wire.setClock(400000);
#endif

  bool initialized = false;
  while (!initialized)
  {
#ifdef USE_SPI
    myICM.begin(CS_PIN, SPI_PORT, SPI_FREQ); // Here we are using the user-defined SPI_FREQ as the clock speed of the SPI bus
#else
    myICM.begin(Wire, AD0_VAL);
#endif
    Serial.print(F("Initialization of the sensor returned: "));
    Serial.println(myICM.statusString());
    if (myICM.status != ICM_20948_Stat_Ok)
    {
      Serial.println("Trying again...");
      delay(500);
    }
    else
    {
      initialized = true;
    }
  }
  Serial.println("Device connected!");
  myICM.swReset();
  if (myICM.status != ICM_20948_Stat_Ok)
  {
    Serial.print(F("Software Reset returned: "));
    Serial.println(myICM.statusString());
  }
  delay(250);
  myICM.sleep(false);
  myICM.lowPower(false);

  myICM.setSampleMode((ICM_20948_Internal_Acc | ICM_20948_Internal_Gyr), ICM_20948_Sample_Mode_Continuous);
  if (myICM.status != ICM_20948_Stat_Ok)
  {
    Serial.print(F("setSampleMode returned: "));
    Serial.println(myICM.statusString());
  }
  // Set full scale ranges for both acc and gyr
  ICM_20948_fss_t myFSS; // This uses a "Full Scale Settings" structure that can contain values for all configurable sensors
  myFSS.a = gpm4; // (ICM_20948_ACCEL_CONFIG_FS_SEL_e) // gpm2 // gpm4 // gpm8 // gpm16
  myFSS.g = dps2000; // (ICM_20948_GYRO_CONFIG_1_FS_SEL_e) // dps250 // dps500 // dps1000 // dps2000
  myICM.setFullScale((ICM_20948_Internal_Acc | ICM_20948_Internal_Gyr), myFSS);
  if (myICM.status != ICM_20948_Stat_Ok)
  {
    Serial.print(F("setFullScale returned: "));
    Serial.println(myICM.statusString());
  }
  // Set up Digital Low-Pass Filter configuration
  ICM_20948_dlpcfg_t myDLPcfg;    // Similar to FSS, this uses a configuration structure for the desired sensors
  myDLPcfg.a = acc_d473bw_n499bw; // (ICM_20948_ACCEL_CONFIG_DLPCFG_e)
                                  // acc_d246bw_n265bw      - means 3db bandwidth is 246 hz and nyquist bandwidth is 265 hz
                                  // acc_d111bw4_n136bw
                                  // acc_d50bw4_n68bw8
                                  // acc_d23bw9_n34bw4
                                  // acc_d11bw5_n17bw
                                  // acc_d5bw7_n8bw3        - means 3 db bandwidth is 5.7 hz and nyquist bandwidth is 8.3 hz
                                  // acc_d473bw_n499bw

  myDLPcfg.g = gyr_d361bw4_n376bw5; // (ICM_20948_GYRO_CONFIG_1_DLPCFG_e)
                                    // gyr_d196bw6_n229bw8
                                    // gyr_d151bw8_n187bw6Serial.print("Initializing SD card...");

  myICM.setDLPFcfg((ICM_20948_Internal_Acc | ICM_20948_Internal_Gyr), myDLPcfg);
  if (myICM.status != ICM_20948_Stat_Ok)
  {
    Serial.print(F("setDLPcfg returned: "));
    Serial.println(myICM.statusString());
  }
  ICM_20948_Status_e accDLPEnableStat = myICM.enableDLPF(ICM_20948_Internal_Acc, false);
  ICM_20948_Status_e gyrDLPEnableStat = myICM.enableDLPF(ICM_20948_Internal_Gyr, false);
  Serial.print(F("Enable DLPF for Accelerometer returned: "));
  Serial.println(myICM.statusString(accDLPEnableStat));
  Serial.print(F("Enable DLPF for Gyroscope returned: "));
  Serial.println(myICM.statusString(gyrDLPEnableStat));
  // Choose whether or not to start the magnetometer
  myICM.startupMagnetometer();
  if (myICM.status != ICM_20948_Stat_Ok)
  {
    Serial.print(F("startupMagnetometer returned: "));
    Serial.println(myICM.statusString());
  }
  Serial.println();
  Serial.println(F("Configuration complete!"));


  // SD Card Setup -------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
  pinMode(cs_pin, OUTPUT);
  Serial.print("Initializing SD card...");
  
  if (!SD.begin(cs_pin)) {
    
    Serial.println("Card failed, or not present");
    
    // Blink Portenta LED Red ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    digitalWrite(LEDR,LOW);                                          
    digitalWrite(LEDG,HIGH);                                        
    digitalWrite(LEDB,HIGH);                                         
    float startTime = millis();
    while (1);
    
  }
  
  const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;

  Serial.println("card initialized.");
  while (SD.exists(fileName))
  {
      if (fileName[BASE_NAME_SIZE + 1] != '9')
      {
        fileName[BASE_NAME_SIZE + 1]++;
      }
      else if (fileName[BASE_NAME_SIZE] != '9')
      {
        fileName[BASE_NAME_SIZE + 1] = '0';
        fileName[BASE_NAME_SIZE]++;
      }
      else
      {
        Serial.println("Can't create file name");
        
        // Blink Portenta LED Red ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
        digitalWrite(LEDR,LOW);                                        
        digitalWrite(LEDG,HIGH);                                        
        digitalWrite(LEDB,HIGH);                                        
      }
  }
  
  // Opening File and Creating Headers +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
  file = SD.open(fileName, FILE_WRITE);

  file.print("currTime");                       file.print(",");
  file.print("s1");                             file.print(",");
  file.print("s2");                             file.print(",");
  file.print("s3");                             file.print(",");
  file.print("s4");                             file.print(",");
  file.print("s");                              file.print(",");
  file.print("AccX");                           file.print(",");
  file.print("AccY");                           file.print(",");
  file.print("AccZ");                           file.print(",");
  file.print("GyroX");                          file.print(",");
  file.print("GyroY");                          file.print(",");
  file.print("GyroZ");                          file.print(",");
  file.print("GRF");
  
//  file.print("s_ax");                           file.print(",");
//  file.print("s_ay");                           file.print(",");
//  file.print("s_az");                           file.print(",");
//  file.print("s_gx");                           file.print(",");
//  file.print("s_gy");                           file.print(",");
//  file.print("s_gz");                                                    
  
  file.println();
  file.close();                                                                                      // Closing File in setup
  
  Serial.println("s1, s2, s3, s4, s, AccX, AccY, AccZ, GyroX, GyroY, GyroZ, GRF");   // Legend for Serial Plot
 
  pcaselect(0);
    // setup the 1st sensor
  mpr1.begin();

  pcaselect(1);
  // setup the 2nd sensor
  mpr2.begin();

  pcaselect(2);
  // setup the 3rd sensor
  mpr3.begin();
  
  pcaselect(3);
  // setup the 4th sensor
  mpr4.begin();

  for (int i = 0; i < avg_size; i++){
      
       baseline_value_1 += mpr1.readPressure();                                     
       baseline_value_2 += mpr2.readPressure();                                       
       baseline_value_3 += mpr3.readPressure();
       baseline_value_4 += mpr4.readPressure();
       
     }
     
  baseline_value_1 /= avg_size;
  baseline_value_2 /= avg_size;
  baseline_value_3 /= avg_size;
  baseline_value_4 /= avg_size;


  // Conditions for Offset selection ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  
  if (baseline_value_1 <= 9000000){
    offset_value_1 = 9000000;
    }
  else if (baseline_value_1 > 9000000){
    offset_value_1 = 9500000;
    }
    
  if (baseline_value_2, baseline_value_3, baseline_value_4  <= 9900000){
    //offset_value_1 = 45500;
    offset_value_2 = 9000000;
    offset_value_3 = 9000000;
    offset_value_4 = 9000000; 
   }
//  if (baseline_value_1 <= 8900000){
//    offset_value_1 = 9500000;
//    }

  delay(1000);
  
}


void loop(){

  count = count + 1;
  file = SD.open(fileName, FILE_WRITE);                                                             // Opening the File in Loop

  if(count%2 == 1)
  {
    // Blink Portenta LED Magenta ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    digitalWrite(LEDR,LOW);                                        
    digitalWrite(LEDG,HIGH);                                         
    digitalWrite(LEDB,LOW);                                         
  }
  
  else{
    
    // Blink Portenta LED Green ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    digitalWrite(LEDR,HIGH);                                        // Blink Portenta Red Light
    digitalWrite(LEDG,LOW);                                         // Blink Portenta Green Light
    digitalWrite(LEDB,HIGH);                                        // Blink Portenta Blue Light
  }
  
  // Data Saving Loop -------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
  float startTime = millis();
  float loopTime = millis();
  while ( ((millis() - startTime)/1000) <= 20){

  cTime = (millis() - startTime);
  
  if (myICM.dataReady())
    {
      myICM.getAGMT();              // The values are only updated when you call 'getAGMT'
      gyroX = myICM.gyrX();   gyroY = myICM.gyrY();   gyroZ = myICM.gyrZ();
      accX  = myICM.accX();   accY  = myICM.accY();   accZ  = myICM.accZ();
    }

   //X_norm = (X - X_min) / (X_max - X_min)
  
  pcaselect(0);

  current_value_1 = mpr1.readPressure();
  //Serial.print(" KPa_1     ");

  pcaselect(1);

  current_value_2 = mpr2.readPressure();
  //Serial.print(" KPa_2     ");

  pcaselect(2);

  current_value_3 = mpr3.readPressure();
  //Serial.print(" KPa_3     ");

  pcaselect(3);
  current_value_4 = mpr4.readPressure();
  //Serial.println(" KPa_4");


  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  
//  final_value_1 = constrain(current_value_1, offset_value_1, 16777216);    
//  final_value_2 = constrain(current_value_2, baseline_value_2+offset_value_2, 16777216);     
//  final_value_3 = constrain(current_value_3, baseline_value_3+offset_value_3, 16777216);     
//  final_value_4 = constrain(current_value_4, baseline_value_4+offset_value_4, 16777216);      
    
  s1 = constrain(current_value_1 - offset_value_1, 580000, 16777216);
  s2 = constrain(current_value_2 - offset_value_2, 580000, 16777216);
  s3 = constrain(current_value_3 - offset_value_3, 580000, 16777216);
  s4 = constrain(current_value_4 - offset_value_4, 580000, 16777216);
  
  s = (s1 + s2 + s3 + s4)/4;
  float s_n = ((s-580000)/(1040937-580000));

  float accX_n = ((accX + 1858.89)/(2458.98+1858.89));
  float accY_n = ((accY + 1815.43)/(3999.88+1815.43));
  float accZ_n = ((accZ + 1763.67)/(3844.24+1763.67));
  float gyroX_n = ((gyroX + 271.77)/(270.67+271.77));
  float gyroY_n = ((gyroY + 132.44)/(237.01+132.44));
  float gyroZ_n = ((gyroZ + 332.20)/(369.09+332.20));

  float s_ax = accX_n * s_n; // Calculate interaction feature s*ax
  float s_ay = accY_n * s_n; // Calculate interaction feature s*ay
  float s_az = accZ_n * s_n; // Calculate interaction feature s*az
  float s_gx = gyroX_n * s_n; // Calculate interaction feature s*gx
  float s_gy = gyroY_n * s_n; // Calculate interaction feature s*gy
  float s_gz = gyroZ_n * s_n; // Calculate interaction feature s*gz
  
//  float s_ax = accX_n * s_n; // Calculate interaction feature s*ax
//  float s_ay = accY_n * s_n; // Calculate interaction feature s*ay
//  float s_az = accZ_n * s_n; // Calculate interaction feature s*az
//  float s_gx = gyroX_n * s_n; // Calculate interaction feature s*gx
//  float s_gy = gyroY_n * s_n; // Calculate interaction feature s*gy
//  float s_gz = gyroZ_n * s_n; // Calculate interaction feature s*gz

  double inputs[] = {s_n, accX_n, accY_n, accZ_n, gyroX_n, gyroY_n, gyroZ_n, s_ax, s_ay, s_az, s_gx, s_gy, s_gz};
  double output[1];
  
  mlp.feedforward(inputs, output);
  
  Write_SDcard();
  grf = constrain(output[0], 0.30, 1);
  Serial.print(s1); 
  Serial.print("  "); Serial.print(s2); Serial.print("  "); Serial.print(s3); Serial.print("  "); Serial.print(s4); Serial.print("  "); Serial.print(s); Serial.print("  ");  Serial.print("Neural Network Output: "); Serial.println(grf);
  //Serial.print("  "); Serial.print(accX, 3); Serial.print("  "); Serial.print(accY, 3); Serial.print("  "); Serial.print(accZ, 3); Serial.print("  "); Serial.print(gyroX, 3); Serial.print("  "); Serial.print(gyroY, 3); Serial.print("  "); Serial.print(gyroZ, 3);  Serial.print("  "); 
  
  
  }
    
    // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    file.close();                                                                               // Closing File in Loop

   // -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   
}


void Write_SDcard()
{
  if (file){
    
    file.print((cTime));                  file.print(",");
    
    file.print((s1));                     file.print(",");
    file.print((s2));                     file.print(",");
    file.print((s3));                     file.print(",");
    file.print((s4));                     file.print(",");
    file.print((s));                      file.print(","); 
    
    file.print((accX));                   file.print(",");
    file.print((accY));                   file.print(","); 
    file.print((accZ));                   file.print(",");
    file.print((gyroX));                  file.print(",");
    file.print((gyroY));                  file.print(",");
    file.print((gyroZ));                  file.print(",");
    file.print((grf));

//    file.print((s_ax));                   file.print(","); 
//    file.print((s_ay));                   file.print(","); 
//    file.print((s_az));                   file.print(","); 
//    file.print((s_gx));                   file.print(","); 
//    file.print((s_gy));                   file.print(","); 
//    file.print((s_gz));                            
    
    file.println();                       //End of Row move to next row
    
  }
  
}
