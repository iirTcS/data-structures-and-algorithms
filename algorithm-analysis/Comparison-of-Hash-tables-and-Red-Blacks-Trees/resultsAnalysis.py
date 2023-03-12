#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt

def plotMes(op, op_nr, path):
    plt.clf()
    print(np.mean(op))
    plt.plot(op_nr, op, "bo")
    f = 0
    for x, y in zip(op_nr, op):
        f+=1
        plt.text(x, y, str(f), color="red", fontsize=12)

    plt.ylabel("average time [ns]")
    plt.xlabel("number of operations")
    # plt.show()
    plt.savefig(path)


def collision() :
    i = np.array([226.04651, 262.06088, 230.17479, 203.7784, 142.29892, 81.925, 89.4, 66.04, 60.1575, 60.92, 131.75, 63.25, 81.8, 80.05, 61.81, 85.64723, 89.39382, 132.08537, 86.85937, 88.62049, 176.76161, 130.61072, 178.04785, 330.37033, 89.33936, 90.86116, 76.74074, 83.11199, 69.54294, 126.13784, 109.8922, 81.5421, 112.07729, 105.816895, 141.94766, 251.41553, 251.19391, 276.33295, 189.01344, 198.21844])
    i_number = np.array([430, 854, 2174, 4314, 21497, 4000, 8000, 20000, 40000, 50000, 400, 800, 2000, 4000, 20000, 50067, 50018, 49948, 49853, 49967, 45924, 11986, 34024, 18956, 7523, 1138, 675, 5572, 26736, 1538, 1577, 26639, 3933, 3954, 58008, 12045, 4858, 10897, 53702, 60004])
    plotMes(i,i_number, "images/collision_insert.png")

    d = np.array([238.87589, 427.36722, 902.26013, 526.1091, 607.2563, 269.66824, 361.8267, 473.3942, 867.38556, 699.96246, 85.71429, 97.095436, 93.56913, 125.69706, 333.2868, 16007.302, 17247.19, 5023.254, 15647.217, 15543.388, 531.1706, 442.82266, 498.38687, 576.7854, 143.93636, 110.77058, 91.304344, 204.4496, 148.30199, 117.02945, 123.10582, 273.79675, 191.08861, 187.59729, 946.899, 422.94113, 328.9986, 403.45547, 956.48035, 1309.3158])
    d_number = np.array([427, 866, 2168, 4328, 21595, 1266, 2562, 6352, 12844, 15978, 126, 241, 622, 1327, 6447, 49933, 49982, 50052, 50147, 50033, 46037, 12017, 34033, 18833, 7479, 1142, 690, 5596, 26796, 1562, 1597, 26657, 3950, 3983, 58046, 12009, 4983, 11026, 53454, 59834])
    plotMes(d,d_number, "images/collision_delete.png")

    c = np.array([3008.9946, 5681.285, 23045.176, 17535.736, 99020.445, 14766.263, 42385.01, 105945.4, 158717.53, 136664.1, 1085.4166, 2202.682, 4953.046, 14208.379, 132807.3, 106237.94, 141434.8, 90551.94, 38796.324, 19974.607, 5923.153, 1922.342, 93748.11, 277739.66, 9097.508, 8521.136, 458114.47, 50527.133, 47176.934, 198153.34, 34358.78, 31692.486, 33964.242, 196915.88, 339072.62])
    c_number = np.array([189, 358, 943, 1900, 9514, 1319, 2542, 6469, 12828, 16053, 144, 261, 673, 1289, 6319, 6060, 1966, 4049, 14124, 701, 609, 649, 636, 643, 642, 634, 635, 656, 672, 30291, 30319, 19994, 50285, 50540, 49870])
    plotMes(c,c_number, "images/collision_contains.png")

    s = np.array([684.8958, 775.9901, 1122.1414, 633.1937, 1142.962, 390.49127, 661.25916, 835.9282, 1399.1791, 1126.8977, 138.26086, 168.65672, 154.68999, 202.1121, 607.25446, 2226.321, 1932.9347, 2052.3474, 827.8341, 466.71732, 137.65625, 94.98567, 967.5079, 1455.9486, 177.72021, 186.23718, 4653.4375, 588.93744, 565.9875, 1911.5918, 477.9035, 366.12662, 406.54868, 2032.3434, 3002.419])
    s_number = np.array([192, 404, 962, 1910, 9534, 1262, 2589, 6410, 12790, 16046, 115, 268, 629, 1231, 6465, 5942, 2007, 3962, 14105, 658, 640, 698, 634, 622, 579, 683, 640, 687, 638, 6056, 6010, 4012, 10170, 9866, 10087])
    plotMes(s,s_number, "images/collision_swap.png")

    p = np.array([72309.52, 234687.5, 208646.39, 189074.48, 783394.0, 107313.73, 314699.03, 703648.56, 1175368.6, 1246171.9, 11380.0, 24143.334, 47448.684, 102259.48, 748542.5, 1088743.0, 390547.9, 851564.56, 286736.88, 161437.53, 27136.06, 9853.4375, 199901.58, 974679.25, 36107.0, 38663.18, 1374274.0, 148409.27, 128962.32, 1540248.5, 263164.22, 104228.695, 172908.89, 1394648.4, 1703912.9])
    p_number = np.array([21, 40, 97, 192, 954, 153, 307, 769, 1538, 1923, 15, 30, 76, 153, 769, 6036, 2023, 3931, 13981, 698, 660, 640, 636, 616, 657, 698, 674, 701, 637, 6030, 6046, 3966, 10111, 9991, 10117])
    plotMes(p,p_number, "images/collision_print.png")


def openA() :
    i = np.array([172.09302, 161.7096, 76.35695, 85.605, 41.09876, 39.525, 34.775, 35.03, 35.6775, 35.67, 40.5, 35.875, 37.1, 36.375, 35.93, 110.87543, 111.975685, 121.350204, 115.17662, 112.626335, 59.145546, 64.984146, 57.177288, 142.27158, 48.17227, 150.52724, 171.40741, 60.445084, 42.302513, 118.59558, 107.98985, 40.02778, 58.581234, 61.02681, 145.18687, 186.4425, 223.85756, 253.89557, 168.5263, 144.5087])
    i_number = np.array([430, 854, 2174, 4314, 21497, 4000, 8000, 20000, 40000, 50000, 400, 800, 2000, 4000, 20000, 50067, 50018, 49948, 49853, 49967, 45924, 11986, 34024, 18956, 7523, 1138, 675, 5572, 26736, 1538, 1577, 26639, 3933, 3954, 58008, 12045, 4858, 10897, 53702, 60004])
    plotMes(i,i_number, "images/open_insert.png")

    d = np.array([91.803276, 131.98615, 68.35793, 37.54621, 32.530678, 32.859398, 35.089775, 38.57053, 40.314545, 40.18651, 33.333332, 32.780083, 33.279743, 36.39789, 35.939198, 34.896763, 35.50278, 35.199394, 35.26233, 33.491894, 36.368572, 35.166847, 35.888695, 49.275208, 32.156704, 42.732048, 38.84058, 33.881344, 31.515898, 39.56466, 36.130245, 31.357616, 35.594936, 34.64725, 40.85208, 41.777, 44.69195, 49.038635, 49.19557, 39.20179])
    d_number = np.array([427, 866, 2168, 4328, 21595, 1266, 2562, 6352, 12844, 15978, 126, 241, 622, 1327, 6447, 49933, 49982, 50052, 50147, 50033, 46037, 12017, 34033, 18833, 7479, 1142, 690, 5596, 26796, 1562, 1597, 26657, 3950, 3983, 58046, 12009, 4983, 11026, 53454, 59834])
    plotMes(d,d_number, "images/open_delete.png")

    c = np.array([167.72487, 142.73743, 156.09756, 64.26316, 42.2325, 34.116756, 35.44453, 38.475807, 42.266914, 39.66237, 35.416668, 27.586206, 34.026745, 34.290146, 33.549614, 64.12541, 55.035606, 58.681156, 48.06004, 43.081314, 50.90312, 49.61479, 45.28302, 51.010887, 42.056076, 39.90536, 49.133858, 43.292683, 43.45238, 52.82097, 44.173622, 44.93848, 41.87332, 65.02572, 67.28093])
    c_number = np.array([189, 358, 943, 1900, 9514, 1319, 2542, 6469, 12828, 16053, 144, 261, 673, 1289, 6319, 6060, 1966, 4049, 14124, 701, 609, 649, 636, 643, 642, 634, 635, 656, 672, 30291, 30319, 19994, 50285, 50540, 49870])
    plotMes(c,c_number, "images/open_contains.png")

    s = np.array([478.125, 371.53467, 291.0603, 260.62827, 187.06734, 105.07131, 128.50522, 149.39157, 172.95543, 187.08089, 46.086956, 58.58209, 56.120827, 71.64906, 83.2792, 252.42343, 163.2287, 251.08531, 163.41722, 116.8693, 140.15625, 114.75645, 159.14827, 252.25081, 132.12436, 82.43045, 252.5, 123.58079, 119.12225, 185.56804, 88.319466, 79.58624, 81.86824, 236.74234, 164.99455])
    s_number = np.array([192, 404, 962, 1910, 9534, 1262, 2589, 6410, 12790, 16046, 115, 268, 629, 1231, 6465, 5942, 2007, 3962, 14105, 658, 640, 698, 634, 622, 579, 683, 640, 687, 638, 6056, 6010, 4012, 10170, 9866, 10087])
    plotMes(s,s_number, "images/open_swap.png")

    p = np.array([1014904.75, 1089385.0, 1020429.9, 1023790.06, 1573636.1, 932666.06, 1243368.8, 1410772.5, 1804396.4, 1990496.8, 852826.7, 865150.0, 1037842.1, 1207345.8, 1530297.9, 1672394.5, 1127193.4, 1478292.2, 1176298.2, 1089472.1, 861065.0, 843874.1, 1024486.1, 1574522.9, 888161.3, 993181.3, 1517890.1, 954977.1, 950666.25, 2599374.2, 1194168.1, 1070219.2, 1123276.8, 2635466.0, 2387835.2])
    p_number = np.array([21, 40, 97, 192, 954, 153, 307, 769, 1538, 1923, 15, 30, 76, 153, 769, 6036, 2023, 3931, 13981, 698, 660, 640, 636, 616, 657, 698, 674, 701, 637, 6030, 6046, 3966, 10111, 9991, 10117])
    plotMes(p,p_number, "images/open_print.png")


def resize() :
    i = np.array([1324.8837, 1827.8689, 2118.5374, 3659.2258, 69115.53, 5669.725, 6488.5625, 61005.105, 118394.664, 146275.94, 629.9925, 1099.3962, 1625.167, 3426.4026, 28431.324, 90507.484, 131274.0, 112316.87, 101535.914, 103000.88, 203389.94, 19814.879, 76255.266, 24725.918, 7723.287, 880.99384, 1053.763, 14081.885, 33336.348, 2008.4629, 1964.7977, 48495.562, 3606.835, 3526.6907, 155923.67, 22734.824, 15040.331, 28121.223, 158851.94, 154357.1])
    i_number = np.array([430, 854, 2174, 4314, 21497, 4000, 8000, 20000, 40000, 50000, 400, 800, 2000, 4000, 20000, 50067, 50018, 49948, 49853, 49967, 45924, 11986, 34024, 18956, 7523, 1138, 675, 5572, 26736, 1538, 1577, 26639, 3933, 3954, 58008, 12045, 4858, 10897, 53702, 60004])
    plotMes(i,i_number, "images/resize_insert.png")

    d = np.array([566.97894, 1119.515, 1374.7694, 3267.6987, 53301.465, 5289.8105, 5251.21, 39973.93, 426780.34, 400570.12, 372.2381, 741.5228, 1635.8344, 2402.0603, 143073.81, 37611.58, 46592.938, 34951.004, 43200.117, 35430.0, 163254.36, 36981.305, 253747.28, 22727.49, 16521.479, 642.8231, 280.14346, 14674.025, 135902.53, 1546.2299, 1173.846, 73418.38, 2563.9011, 2437.5862, 495786.78, 34982.79, 4447.1567, 11207.957, 510318.97, 457145.2])
    d_number = np.array([427, 866, 2168, 4328, 21595, 1266, 2562, 6352, 12844, 15978, 126, 241, 622, 1327, 6447, 49933, 49982, 50052, 50147, 50033, 46037, 12017, 34033, 18833, 7479, 1142, 690, 5596, 26796, 1562, 1597, 26657, 3950, 3983, 58046, 12009, 4983, 11026, 53454, 59834])
    plotMes(d,d_number, "images/resize_delete.png")

    c = np.array([7648.6772, 10417.877, 20899.045, 26406.895, 198247.77, 40540.105, 56044.766, 168518.94, 764115.0, 879818.06, 2946.5, 5832.9272, 15079.471, 22755.541, 302693.97, 633487.6, 322519.84, 645224.94, 240691.81, 119296.58, 15972.563, 6693.3975, 149942.78, 629254.56, 39378.074, 28242.908, 474323.0, 109030.98, 72327.05, 3479652.8, 291883.25, 63044.797, 157237.33, 3695259.8, 3500406.5])
    c_number = np.array([189, 358, 943, 1900, 9514, 1319, 2542, 6469, 12828, 16053, 144, 261, 673, 1289, 6319, 6060, 1966, 4049, 14124, 701, 609, 649, 636, 643, 642, 634, 635, 656, 672, 30291, 30319, 19994, 50285, 50540, 49870])
    plotMes(c,c_number, "images/resize_contains.png")

    s = np.array([996.875, 2125.99, 2770.894, 7029.4243, 134184.7, 9213.708, 9792.159, 61862.215, 671572.25, 654296.8, 646.0696, 1182.4403, 3237.07, 4142.2188, 350465.7, 321391.25, 63425.457, 597449.0, 31400.318, 11723.424, 631.8719, 279.50717, 15103.62, 230340.62, 1179.8169, 1074.1099, 134413.12, 3474.2314, 2860.177, 517151.28, 22197.648, 2892.249, 9509.913, 538455.94, 528572.25])
    s_number = np.array([192, 404, 962, 1910, 9534, 1262, 2589, 6410, 12790, 16046, 115, 268, 629, 1231, 6465, 5942, 2007, 3962, 14105, 658, 640, 698, 634, 622, 579, 683, 640, 687, 638, 6056, 6010, 4012, 10170, 9866, 10087])
    plotMes(s,s_number, "images/resize_swap.png")

    p = np.array([120766.664, 125450.0, 142161.86, 190214.06, 1195145.6, 178093.47, 256531.28, 921583.6, 2953098.2, 3135606.5, 14593.2, 28360.166, 65572.35, 130639.84, 1250448.4, 2557693.0, 526799.2, 2089582.5, 432934.66, 212132.52, 27560.006, 10909.193, 214455.17, 1437716.9, 41592.863, 45571.49, 1073041.6, 170304.0, 127145.37, 4599020.5, 429235.38, 112993.36, 255060.06, 4726155.5, 5042096.5])
    p_number = np.array([21, 40, 97, 192, 954, 153, 307, 769, 1538, 1923, 15, 30, 76, 153, 769, 6036, 2023, 3931, 13981, 698, 660, 640, 636, 616, 657, 698, 674, 701, 637, 6030, 6046, 3966, 10111, 9991, 10117])
    plotMes(p,p_number, "images/resize_print.png")


def rbt():
    i = np.array([385.81396, 282.08432, 198.52806, 160.63977, 84.51877, 74.375, 80.0875, 80.625, 96.7375, 86.876, 75.0, 79.375, 102.9, 94.95, 86.925, 528.6995, 541.667, 321.0539, 542.6033, 507.92923, 170.10495, 141.27315, 151.09335, 264.9926, 113.09318, 113.356766, 126.22222, 99.55133, 118.20018, 104.35631, 120.98922, 117.31672, 120.77295, 119.47395, 595.72815, 321.72687, 288.67847, 394.72333, 746.1342, 583.54443])
    i_number = np.array([430, 854, 2174, 4314, 21497, 4000, 8000, 20000, 40000, 50000, 400, 800, 2000, 4000, 20000, 50067, 50018, 49948, 49853, 49967, 45924, 11986, 34024, 18956, 7523, 1138, 675, 5572, 26736, 1538, 1577, 26639, 3933, 3954, 58008, 12045, 4858, 10897, 53702, 60004])
    plotMes(i,i_number, "images/rbtree_insert.png")

    d = np.array([399.53162, 233.71825, 144.88008, 108.710724, 70.868256, 95.18167, 105.58157, 139.38918, 160.1526, 138.65941, 96.82539, 106.63901, 87.13826, 101.4318, 137.59888, 454.475, 466.83005, 266.9064, 464.5582, 433.95758, 197.65189, 124.11584, 159.13966, 203.97707, 131.00682, 96.84763, 86.521736, 94.97855, 116.09942, 107.490395, 117.532875, 111.14904, 150.7848, 119.25684, 380.00723, 155.43343, 162.61288, 220.77817, 454.91263, 218.43434])
    d_number = np.array([427, 866, 2168, 4328, 21595, 1266, 2562, 6352, 12844, 15978, 126, 241, 622, 1327, 6447, 49933, 49982, 50052, 50147, 50033, 46037, 12017, 34033, 18833, 7479, 1142, 690, 5596, 26796, 1562, 1597, 26657, 3950, 3983, 58046, 12009, 4983, 11026, 53454, 59834])
    plotMes(d,d_number, "images/rbtree_delete.png")

    c = np.array([273.01587, 298.32404, 137.96394, 104.36842, 65.67164, 50.871872, 58.615265, 67.67661, 82.312126, 65.807014, 39.583332, 47.12644, 50.22288, 59.270752, 72.464, 553.54785, 248.32147, 461.00272, 197.59982, 214.9786, 96.05911, 82.5886, 149.37106, 1233.5925, 104.6729, 119.71609, 1141.5748, 202.7439, 207.44048, 706.6785, 169.40202, 164.37431, 212.0712, 871.1555, 400.10428])
    c_number = np.array([189, 358, 943, 1900, 9514, 1319, 2542, 6469, 12828, 16053, 144, 261, 673, 1289, 6319, 6060, 1966, 4049, 14124, 701, 609, 649, 636, 643, 642, 634, 635, 656, 672, 30291, 30319, 19994, 50285, 50540, 49870])
    plotMes(c,c_number, "images/rbtree_contains.png")

    s = np.array([1501.0416, 643.31683, 752.079, 508.95288, 484.07803, 253.16957, 432.90845, 592.0437, 718.58484, 648.1927, 178.26086, 205.97015, 238.47377, 302.84323, 491.94122, 1388.0848, 443.1988, 1227.9404, 330.2304, 348.63223, 101.40625, 90.687675, 189.74763, 2187.4597, 113.98964, 181.40556, 1906.4062, 248.03493, 248.90282, 767.80054, 170.9817, 166.87437, 216.0472, 950.0, 366.9872])
    s_number = np.array([192, 404, 962, 1910, 9534, 1262, 2589, 6410, 12790, 16046, 115, 268, 629, 1231, 6465, 5942, 2007, 3962, 14105, 658, 640, 698, 634, 622, 579, 683, 640, 687, 638, 6056, 6010, 4012, 10170, 9866, 10087])
    plotMes(s,s_number, "images/rbtree_swap.png")

    p = np.array([63371.43, 46012.5, 111171.13, 175049.48, 660933.44, 104339.87, 179288.6, 666473.6, 1272304.4, 1030460.06, 9673.333, 17740.0, 56639.473, 120116.99, 811613.3, 1068502.6, 310135.9, 924002.94, 216621.4, 181044.56, 16474.848, 6800.9375, 105225.47, 1946206.8, 25151.598, 25969.342, 2044481.9, 92460.77, 90509.266, 1435027.5, 209693.48, 86391.66, 187445.27, 1449212.2, 1371824.6])
    p_number = np.array([21, 40, 97, 192, 954, 153, 307, 769, 1538, 1923, 15, 30, 76, 153, 769, 6036, 2023, 3931, 13981, 698, 660, 640, 636, 616, 657, 698, 674, 701, 637, 6030, 6046, 3966, 10111, 9991, 10117])
    plotMes(p,p_number, "images/rbtree_print.png")


def plotSpecific(v1, v2, v3, v4, path):
    plt.clf()
    plt.plot(0, v1, "ro")
    plt.plot(1 ,v2, "bo")
    # plt.plot(2 ,v3, "go")
    # plt.plot(3, v4, "o")
    plt.ylabel("average time [ns]")
    plt.xlabel("red - rbtree / blue - open address")
    plt.title(path)
    plt.savefig(path)


def insert_t():
    rbti = np.mean(np.array([385.81396, 282.08432, 198.52806, 160.63977, 84.51877, 74.375, 80.0875, 80.625, 96.7375, 86.876, 75.0, 79.375, 102.9, 94.95, 86.925, 528.6995, 541.667, 321.0539, 542.6033, 507.92923, 170.10495, 141.27315, 151.09335, 264.9926, 113.09318, 113.356766, 126.22222, 99.55133, 118.20018, 104.35631, 120.98922, 117.31672, 120.77295, 119.47395, 595.72815, 321.72687, 288.67847, 394.72333, 746.1342, 583.54443]))
    openi =  np.mean(np.array([172.09302, 161.7096, 76.35695, 85.605, 41.09876, 39.525, 34.775, 35.03, 35.6775, 35.67, 40.5, 35.875, 37.1, 36.375, 35.93, 110.87543, 111.975685, 121.350204, 115.17662, 112.626335, 59.145546, 64.984146, 57.177288, 142.27158, 48.17227, 150.52724, 171.40741, 60.445084, 42.302513, 118.59558, 107.98985, 40.02778, 58.581234, 61.02681, 145.18687, 186.4425, 223.85756, 253.89557, 168.5263, 144.5087]))
    resizei =  np.mean(np.array([1324.8837, 1827.8689, 2118.5374, 3659.2258, 69115.53, 5669.725, 6488.5625, 61005.105, 118394.664, 146275.94, 629.9925, 1099.3962, 1625.167, 3426.4026, 28431.324, 90507.484, 131274.0, 112316.87, 101535.914, 103000.88, 203389.94, 19814.879, 76255.266, 24725.918, 7723.287, 880.99384, 1053.763, 14081.885, 33336.348, 2008.4629, 1964.7977, 48495.562, 3606.835, 3526.6907, 155923.67, 22734.824, 15040.331, 28121.223, 158851.94, 154357.1]))
    colli =  np.mean(np.array([226.04651, 262.06088, 230.17479, 203.7784, 142.29892, 81.925, 89.4, 66.04, 60.1575, 60.92, 131.75, 63.25, 81.8, 80.05, 61.81, 85.64723, 89.39382, 132.08537, 86.85937, 88.62049, 176.76161, 130.61072, 178.04785, 330.37033, 89.33936, 90.86116, 76.74074, 83.11199, 69.54294, 126.13784, 109.8922, 81.5421, 112.07729, 105.816895, 141.94766, 251.41553, 251.19391, 276.33295, 189.01344, 198.21844]))
    plotSpecific(rbti, openi, resizei, colli, "images/insert_rbtod.png")

def delete_t():
    rbti = np.mean(np.array([399.53162, 233.71825, 144.88008, 108.710724, 70.868256, 95.18167, 105.58157, 139.38918, 160.1526, 138.65941, 96.82539, 106.63901, 87.13826, 101.4318, 137.59888, 454.475, 466.83005, 266.9064, 464.5582, 433.95758, 197.65189, 124.11584, 159.13966, 203.97707, 131.00682, 96.84763, 86.521736, 94.97855, 116.09942, 107.490395, 117.532875, 111.14904, 150.7848, 119.25684, 380.00723, 155.43343, 162.61288, 220.77817, 454.91263, 218.43434]))
    openi =  np.mean(np.array([91.803276, 131.98615, 68.35793, 37.54621, 32.530678, 32.859398, 35.089775, 38.57053, 40.314545, 40.18651, 33.333332, 32.780083, 33.279743, 36.39789, 35.939198, 34.896763, 35.50278, 35.199394, 35.26233, 33.491894, 36.368572, 35.166847, 35.888695, 49.275208, 32.156704, 42.732048, 38.84058, 33.881344, 31.515898, 39.56466, 36.130245, 31.357616, 35.594936, 34.64725, 40.85208, 41.777, 44.69195, 49.038635, 49.19557, 39.20179]))
    resizei =  np.mean(np.array([566.97894, 1119.515, 1374.7694, 3267.6987, 53301.465, 5289.8105, 5251.21, 39973.93, 426780.34, 400570.12, 372.2381, 741.5228, 1635.8344, 2402.0603, 143073.81, 37611.58, 46592.938, 34951.004, 43200.117, 35430.0, 163254.36, 36981.305, 253747.28, 22727.49, 16521.479, 642.8231, 280.14346, 14674.025, 135902.53, 1546.2299, 1173.846, 73418.38, 2563.9011, 2437.5862, 495786.78, 34982.79, 4447.1567, 11207.957, 510318.97, 457145.2]))
    colli =  np.mean(np.array([238.87589, 427.36722, 902.26013, 526.1091, 607.2563, 269.66824, 361.8267, 473.3942, 867.38556, 699.96246, 85.71429, 97.095436, 93.56913, 125.69706, 333.2868, 16007.302, 17247.19, 5023.254, 15647.217, 15543.388, 531.1706, 442.82266, 498.38687, 576.7854, 143.93636, 110.77058, 91.304344, 204.4496, 148.30199, 117.02945, 123.10582, 273.79675, 191.08861, 187.59729, 946.899, 422.94113, 328.9986, 403.45547, 956.48035, 1309.3158]))
    plotSpecific(rbti, openi, resizei, colli, "images/delete_rbtod.png")


def contains_t():
    rbti = np.mean(np.array([273.01587, 298.32404, 137.96394, 104.36842, 65.67164, 50.871872, 58.615265, 67.67661, 82.312126, 65.807014, 39.583332, 47.12644, 50.22288, 59.270752, 72.464, 553.54785, 248.32147, 461.00272, 197.59982, 214.9786, 96.05911, 82.5886, 149.37106, 1233.5925, 104.6729, 119.71609, 1141.5748, 202.7439, 207.44048, 706.6785, 169.40202, 164.37431, 212.0712, 871.1555, 400.10428]))
    openi =  np.mean(np.array([167.72487, 142.73743, 156.09756, 64.26316, 42.2325, 34.116756, 35.44453, 38.475807, 42.266914, 39.66237, 35.416668, 27.586206, 34.026745, 34.290146, 33.549614, 64.12541, 55.035606, 58.681156, 48.06004, 43.081314, 50.90312, 49.61479, 45.28302, 51.010887, 42.056076, 39.90536, 49.133858, 43.292683, 43.45238, 52.82097, 44.173622, 44.93848, 41.87332, 65.02572, 67.28093]))
    resizei =  np.mean(np.array([7648.6772, 10417.877, 20899.045, 26406.895, 198247.77, 40540.105, 56044.766, 168518.94, 764115.0, 879818.06, 2946.5, 5832.9272, 15079.471, 22755.541, 302693.97, 633487.6, 322519.84, 645224.94, 240691.81, 119296.58, 15972.563, 6693.3975, 149942.78, 629254.56, 39378.074, 28242.908, 474323.0, 109030.98, 72327.05, 3479652.8, 291883.25, 63044.797, 157237.33, 3695259.8, 3500406.5]))
    colli =  np.mean(np.array([3008.9946, 5681.285, 23045.176, 17535.736, 99020.445, 14766.263, 42385.01, 105945.4, 158717.53, 136664.1, 1085.4166, 2202.682, 4953.046, 14208.379, 132807.3, 106237.94, 141434.8, 90551.94, 38796.324, 19974.607, 5923.153, 1922.342, 93748.11, 277739.66, 9097.508, 8521.136, 458114.47, 50527.133, 47176.934, 198153.34, 34358.78, 31692.486, 33964.242, 196915.88, 339072.62]))
    plotSpecific(rbti, openi, resizei, colli, "images/contains_rbtod.png")


def swap_t():
    rbti = np.mean(np.array([1501.0416, 643.31683, 752.079, 508.95288, 484.07803, 253.16957, 432.90845, 592.0437, 718.58484, 648.1927, 178.26086, 205.97015, 238.47377, 302.84323, 491.94122, 1388.0848, 443.1988, 1227.9404, 330.2304, 348.63223, 101.40625, 90.687675, 189.74763, 2187.4597, 113.98964, 181.40556, 1906.4062, 248.03493, 248.90282, 767.80054, 170.9817, 166.87437, 216.0472, 950.0, 366.9872]))
    openi =  np.mean(np.array([478.125, 371.53467, 291.0603, 260.62827, 187.06734, 105.07131, 128.50522, 149.39157, 172.95543, 187.08089, 46.086956, 58.58209, 56.120827, 71.64906, 83.2792, 252.42343, 163.2287, 251.08531, 163.41722, 116.8693, 140.15625, 114.75645, 159.14827, 252.25081, 132.12436, 82.43045, 252.5, 123.58079, 119.12225, 185.56804, 88.319466, 79.58624, 81.86824, 236.74234, 164.99455]))
    resizei =  np.mean(np.array([996.875, 2125.99, 2770.894, 7029.4243, 134184.7, 9213.708, 9792.159, 61862.215, 671572.25, 654296.8, 646.0696, 1182.4403, 3237.07, 4142.2188, 350465.7, 321391.25, 63425.457, 597449.0, 31400.318, 11723.424, 631.8719, 279.50717, 15103.62, 230340.62, 1179.8169, 1074.1099, 134413.12, 3474.2314, 2860.177, 517151.28, 22197.648, 2892.249, 9509.913, 538455.94, 528572.25]))
    colli =  np.mean(np.array([684.8958, 775.9901, 1122.1414, 633.1937, 1142.962, 390.49127, 661.25916, 835.9282, 1399.1791, 1126.8977, 138.26086, 168.65672, 154.68999, 202.1121, 607.25446, 2226.321, 1932.9347, 2052.3474, 827.8341, 466.71732, 137.65625, 94.98567, 967.5079, 1455.9486, 177.72021, 186.23718, 4653.4375, 588.93744, 565.9875, 1911.5918, 477.9035, 366.12662, 406.54868, 2032.3434, 3002.419]))
    plotSpecific(rbti, openi, resizei, colli, "images/swap_rbtod.png")

def print_t():
    rbti = np.mean(np.array([63371.43, 46012.5, 111171.13, 175049.48, 660933.44, 104339.87, 179288.6, 666473.6, 1272304.4, 1030460.06, 9673.333, 17740.0, 56639.473, 120116.99, 811613.3, 1068502.6, 310135.9, 924002.94, 216621.4, 181044.56, 16474.848, 6800.9375, 105225.47, 1946206.8, 25151.598, 25969.342, 2044481.9, 92460.77, 90509.266, 1435027.5, 209693.48, 86391.66, 187445.27, 1449212.2, 1371824.6]))
    openi =  np.mean(np.array([1014904.75, 1089385.0, 1020429.9, 1023790.06, 1573636.1, 932666.06, 1243368.8, 1410772.5, 1804396.4, 1990496.8, 852826.7, 865150.0, 1037842.1, 1207345.8, 1530297.9, 1672394.5, 1127193.4, 1478292.2, 1176298.2, 1089472.1, 861065.0, 843874.1, 1024486.1, 1574522.9, 888161.3, 993181.3, 1517890.1, 954977.1, 950666.25, 2599374.2, 1194168.1, 1070219.2, 1123276.8, 2635466.0, 2387835.2]))
    resizei =  np.mean(np.array([120766.664, 125450.0, 142161.86, 190214.06, 1195145.6, 178093.47, 256531.28, 921583.6, 2953098.2, 3135606.5, 14593.2, 28360.166, 65572.35, 130639.84, 1250448.4, 2557693.0, 526799.2, 2089582.5, 432934.66, 212132.52, 27560.006, 10909.193, 214455.17, 1437716.9, 41592.863, 45571.49, 1073041.6, 170304.0, 127145.37, 4599020.5, 429235.38, 112993.36, 255060.06, 4726155.5, 5042096.5]))
    colli =  np.mean(np.array([72309.52, 234687.5, 208646.39, 189074.48, 783394.0, 107313.73, 314699.03, 703648.56, 1175368.6, 1246171.9, 11380.0, 24143.334, 47448.684, 102259.48, 748542.5, 1088743.0, 390547.9, 851564.56, 286736.88, 161437.53, 27136.06, 9853.4375, 199901.58, 974679.25, 36107.0, 38663.18, 1374274.0, 148409.27, 128962.32, 1540248.5, 263164.22, 104228.695, 172908.89, 1394648.4, 1703912.9]))
    plotSpecific(rbti, openi, resizei, colli, "images/print_rbtod.png")

def comp_res():
    i1 = np.array([1324.8837, 1827.8689, 2118.5374, 3659.2258, 69115.53, 5669.725, 6488.5625, 61005.105, 118394.664, 146275.94, 629.9925, 1099.3962, 1625.167, 3426.4026, 28431.324, 90507.484, 131274.0, 112316.87, 101535.914, 103000.88, 203389.94, 19814.879, 76255.266, 24725.918, 7723.287, 880.99384, 1053.763, 14081.885, 33336.348, 2008.4629, 1964.7977, 48495.562, 3606.835, 3526.6907, 155923.67, 22734.824, 15040.331, 28121.223, 158851.94, 154357.1])
    i_number = np.array([430, 854, 2174, 4314, 21497, 4000, 8000, 20000, 40000, 50000, 400, 800, 2000, 4000, 20000, 50067, 50018, 49948, 49853, 49967, 45924, 11986, 34024, 18956, 7523, 1138, 675, 5572, 26736, 1538, 1577, 26639, 3933, 3954, 58008, 12045, 4858, 10897, 53702, 60004])
    i2 = np.array([773.9535, 1233.9579, 2730.0369, 5454.196, 22475.281, 4345.775, 8917.838, 19582.975, 55652.61, 58144.363, 421.0, 968.375, 2145.4, 4438.575, 19888.004, 58401.41, 79330.59, 55518.887, 56397.223, 57017.25, 69695.836, 16761.914, 37968.8, 41252.23, 7972.405, 25666.871, 31032.445, 21013.12, 20308.404, 24542.912, 21573.178, 19890.463, 20341.545, 20689.783, 102495.305, 38215.633, 41267.54, 46118.656, 125247.22, 132651.95])

    plt.clf()
    plt.plot(i_number, i1, "ro")
    plt.plot(i_number ,i2, "bo")
    plt.savefig("images/comp_res.png")

def main():
    # collision()
    # openA()
    # resize()
    # rbt()
    insert_t()
    delete_t()
    contains_t()
    swap_t()
    print_t()

if __name__ == '__main__' :
    main()
    # comp_res()