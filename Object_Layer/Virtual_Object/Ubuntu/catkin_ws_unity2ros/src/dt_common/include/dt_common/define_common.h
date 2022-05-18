/*
© Guangdong University of Technology,
© The Laboratory of Intelligent Decision and Cooperative Control,
© 2021-2022,
© Author: Yuanlin Yang (yongwang0808@163.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
<http://www.apache.org/licenses/LICENSE-2.0>.
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef DEFINE_COMMON_H
#define DEFINE_COMMON_H
#include "x2struct/x2struct.hpp"
using namespace std;
namespace DTUAV {
/*
 * ==========================> Define Object ID <=======================================
*/
//-------------------------->The Object Id for Physical Uav (1-->100)<--------------------------------
#define R_UAV_0  1
#define R_UAV_1  2
#define R_UAV_2  3
#define R_UAV_3  4
#define R_UAV_4  5
#define R_UAV_5  6
#define R_UAV_6  7
#define R_UAV_7  8
#define R_UAV_8  9
#define R_UAV_9  10

#define R_UAV_10 11
#define R_UAV_11 12
#define R_UAV_12 13
#define R_UAV_13 14
#define R_UAV_14 15
#define R_UAV_15 16
#define R_UAV_16 17
#define R_UAV_17 18
#define R_UAV_18 19
#define R_UAV_19 20

#define R_UAV_20 21
#define R_UAV_21 22
#define R_UAV_22 23
#define R_UAV_23 24
#define R_UAV_24 25
#define R_UAV_25 26
#define R_UAV_26 27
#define R_UAV_27 28
#define R_UAV_28 29
#define R_UAV_29 30

#define R_UAV_30 31
#define R_UAV_31 32
#define R_UAV_32 33
#define R_UAV_33 34
#define R_UAV_34 35
#define R_UAV_35 36
#define R_UAV_36 37
#define R_UAV_37 38
#define R_UAV_38 39
#define R_UAV_39 40

#define R_UAV_40 41
#define R_UAV_41 42
#define R_UAV_42 43
#define R_UAV_43 44
#define R_UAV_44 45
#define R_UAV_45 46
#define R_UAV_46 47
#define R_UAV_47 48
#define R_UAV_48 49
#define R_UAV_49 50

#define R_UAV_50 51
#define R_UAV_51 52
#define R_UAV_52 53
#define R_UAV_53 54
#define R_UAV_54 55
#define R_UAV_55 56
#define R_UAV_56 57
#define R_UAV_57 58
#define R_UAV_58 59
#define R_UAV_59 60

#define R_UAV_60 61
#define R_UAV_61 62
#define R_UAV_62 63
#define R_UAV_63 64
#define R_UAV_64 65
#define R_UAV_65 66
#define R_UAV_66 67
#define R_UAV_67 68
#define R_UAV_68 69
#define R_UAV_69 70

#define R_UAV_70 71
#define R_UAV_71 72
#define R_UAV_72 73
#define R_UAV_73 74
#define R_UAV_74 75
#define R_UAV_75 76
#define R_UAV_76 77
#define R_UAV_77 78
#define R_UAV_78 79
#define R_UAV_79 80

#define R_UAV_80 81
#define R_UAV_81 82
#define R_UAV_82 83
#define R_UAV_83 84
#define R_UAV_84 85
#define R_UAV_85 86
#define R_UAV_86 87
#define R_UAV_87 88
#define R_UAV_88 89
#define R_UAV_89 90

#define R_UAV_90 91
#define R_UAV_91 92
#define R_UAV_92 93
#define R_UAV_93 94
#define R_UAV_94 95
#define R_UAV_95 96
#define R_UAV_96 97
#define R_UAV_97 98
#define R_UAV_98 99
#define R_UAV_99 100

//-------------------------->The Object Id for Physical Car (101-->200)<--------------------------------
#define R_CAR_0  101
#define R_CAR_1  102
#define R_CAR_2  103
#define R_CAR_3  104
#define R_CAR_4  105
#define R_CAR_5  106
#define R_CAR_6  107
#define R_CAR_7  108
#define R_CAR_8  109
#define R_CAR_9  110

#define R_CAR_10 111
#define R_CAR_11 112
#define R_CAR_12 113
#define R_CAR_13 114
#define R_CAR_14 115
#define R_CAR_15 116
#define R_CAR_16 117
#define R_CAR_17 118
#define R_CAR_18 119
#define R_CAR_19 120

#define R_CAR_20 121
#define R_CAR_21 122
#define R_CAR_22 123
#define R_CAR_23 124
#define R_CAR_24 125
#define R_CAR_25 126
#define R_CAR_26 127
#define R_CAR_27 128
#define R_CAR_28 129
#define R_CAR_29 130

#define R_CAR_30 131
#define R_CAR_31 132
#define R_CAR_32 133
#define R_CAR_33 134
#define R_CAR_34 135
#define R_CAR_35 136
#define R_CAR_36 137
#define R_CAR_37 138
#define R_CAR_38 139
#define R_CAR_39 140

#define R_CAR_40 141
#define R_CAR_41 142
#define R_CAR_42 143
#define R_CAR_43 144
#define R_CAR_44 145
#define R_CAR_45 146
#define R_CAR_46 147
#define R_CAR_47 148
#define R_CAR_48 149
#define R_CAR_49 150

#define R_CAR_50 151
#define R_CAR_51 152
#define R_CAR_52 153
#define R_CAR_53 154
#define R_CAR_54 155
#define R_CAR_55 156
#define R_CAR_56 157
#define R_CAR_57 158
#define R_CAR_58 159
#define R_CAR_59 160

#define R_CAR_60 161
#define R_CAR_61 162
#define R_CAR_62 163
#define R_CAR_63 164
#define R_CAR_64 165
#define R_CAR_65 166
#define R_CAR_66 167
#define R_CAR_67 168
#define R_CAR_68 169
#define R_CAR_69 170

#define R_CAR_70 171
#define R_CAR_71 172
#define R_CAR_72 173
#define R_CAR_73 174
#define R_CAR_74 175
#define R_CAR_75 176
#define R_CAR_76 177
#define R_CAR_77 178
#define R_CAR_78 179
#define R_CAR_79 180

#define R_CAR_80 181
#define R_CAR_81 182
#define R_CAR_82 183
#define R_CAR_83 184
#define R_CAR_84 185
#define R_CAR_85 186
#define R_CAR_86 187
#define R_CAR_87 188
#define R_CAR_88 189
#define R_CAR_89 190

#define R_CAR_90 191
#define R_CAR_91 192
#define R_CAR_92 193
#define R_CAR_93 194
#define R_CAR_94 195
#define R_CAR_95 196
#define R_CAR_96 197
#define R_CAR_97 198
#define R_CAR_98 199
#define R_CAR_99 200

//-------------------------->The Object Id for Virtual Uav (201-->300)<--------------------------------
#define V_UAV_0  201
#define V_UAV_1  202
#define V_UAV_2  203
#define V_UAV_3  204
#define V_UAV_4  205
#define V_UAV_5  206
#define V_UAV_6  207
#define V_UAV_7  208
#define V_UAV_8  209
#define V_UAV_9  210

#define V_UAV_10 211
#define V_UAV_11 212
#define V_UAV_12 213
#define V_UAV_13 214
#define V_UAV_14 215
#define V_UAV_15 216
#define V_UAV_16 217
#define V_UAV_17 218
#define V_UAV_18 219
#define V_UAV_19 220

#define V_UAV_20 221
#define V_UAV_21 222
#define V_UAV_22 223
#define V_UAV_23 224
#define V_UAV_24 225
#define V_UAV_25 226
#define V_UAV_26 227
#define V_UAV_27 228
#define V_UAV_28 229
#define V_UAV_29 230

#define V_UAV_30 231
#define V_UAV_31 232
#define V_UAV_32 233
#define V_UAV_33 234
#define V_UAV_34 235
#define V_UAV_35 236
#define V_UAV_36 237
#define V_UAV_37 238
#define V_UAV_38 239
#define V_UAV_39 240

#define V_UAV_40 241
#define V_UAV_41 242
#define V_UAV_42 243
#define V_UAV_43 244
#define V_UAV_44 245
#define V_UAV_45 246
#define V_UAV_46 247
#define V_UAV_47 248
#define V_UAV_48 249
#define V_UAV_49 250

#define V_UAV_50 251
#define V_UAV_51 252
#define V_UAV_52 253
#define V_UAV_53 254
#define V_UAV_54 255
#define V_UAV_55 256
#define V_UAV_56 257
#define V_UAV_57 258
#define V_UAV_58 259
#define V_UAV_59 260

#define V_UAV_60 261
#define V_UAV_61 262
#define V_UAV_62 263
#define V_UAV_63 264
#define V_UAV_64 265
#define V_UAV_65 266
#define V_UAV_66 267
#define V_UAV_67 268
#define V_UAV_68 269
#define V_UAV_69 270

#define V_UAV_70 271
#define V_UAV_71 272
#define V_UAV_72 273
#define V_UAV_73 274
#define V_UAV_74 275
#define V_UAV_75 276
#define V_UAV_76 277
#define V_UAV_77 278
#define V_UAV_78 279
#define V_UAV_79 280

#define V_UAV_80 281
#define V_UAV_81 282
#define V_UAV_82 283
#define V_UAV_83 284
#define V_UAV_84 285
#define V_UAV_85 286
#define V_UAV_86 287
#define V_UAV_87 288
#define V_UAV_88 289
#define V_UAV_89 290

#define V_UAV_90 291
#define V_UAV_91 292
#define V_UAV_92 293
#define V_UAV_93 294
#define V_UAV_94 295
#define V_UAV_95 296
#define V_UAV_96 297
#define V_UAV_97 298
#define V_UAV_98 299
#define V_UAV_99 300

//-------------------------->The Object Id for Virtual Car (301-->400)<--------------------------------
#define V_CAR_0  301
#define V_CAR_1  302
#define V_CAR_2  303
#define V_CAR_3  304
#define V_CAR_4  305
#define V_CAR_5  306
#define V_CAR_6  307
#define V_CAR_7  308
#define V_CAR_8  309
#define V_CAR_9  310

#define V_CAR_10 311
#define V_CAR_11 312
#define V_CAR_12 313
#define V_CAR_13 314
#define V_CAR_14 315
#define V_CAR_15 316
#define V_CAR_16 317
#define V_CAR_17 318
#define V_CAR_18 319
#define V_CAR_19 320

#define V_CAR_20 321
#define V_CAR_21 322
#define V_CAR_22 323
#define V_CAR_23 324
#define V_CAR_24 325
#define V_CAR_25 326
#define V_CAR_26 327
#define V_CAR_27 328
#define V_CAR_28 329
#define V_CAR_29 330

#define V_CAR_30 331
#define V_CAR_31 332
#define V_CAR_32 333
#define V_CAR_33 334
#define V_CAR_34 335
#define V_CAR_35 336
#define V_CAR_36 337
#define V_CAR_37 338
#define V_CAR_38 339
#define V_CAR_39 340

#define V_CAR_40 341
#define V_CAR_41 342
#define V_CAR_42 343
#define V_CAR_43 344
#define V_CAR_44 345
#define V_CAR_45 346
#define V_CAR_46 347
#define V_CAR_47 348
#define V_CAR_48 349
#define V_CAR_49 350

#define V_CAR_50 351
#define V_CAR_51 352
#define V_CAR_52 353
#define V_CAR_53 354
#define V_CAR_54 355
#define V_CAR_55 356
#define V_CAR_56 357
#define V_CAR_57 358
#define V_CAR_58 359
#define V_CAR_59 360

#define V_CAR_60 361
#define V_CAR_61 362
#define V_CAR_62 363
#define V_CAR_63 364
#define V_CAR_64 365
#define V_CAR_65 366
#define V_CAR_66 367
#define V_CAR_67 368
#define V_CAR_68 369
#define V_CAR_69 370

#define V_CAR_70 371
#define V_CAR_71 372
#define V_CAR_72 373
#define V_CAR_73 374
#define V_CAR_74 375
#define V_CAR_75 376
#define V_CAR_76 377
#define V_CAR_77 378
#define V_CAR_78 379
#define V_CAR_79 380

#define V_CAR_80 381
#define V_CAR_81 382
#define V_CAR_82 383
#define V_CAR_83 384
#define V_CAR_84 385
#define V_CAR_85 386
#define V_CAR_86 387
#define V_CAR_87 388
#define V_CAR_88 389
#define V_CAR_89 390

#define V_CAR_90 391
#define V_CAR_91 392
#define V_CAR_92 393
#define V_CAR_93 394
#define V_CAR_94 395
#define V_CAR_95 396
#define V_CAR_96 397
#define V_CAR_97 398
#define V_CAR_98 399
#define V_CAR_99 400

//-------------------------->The Object Id for VR Devices (401-->450)<--------------------------------
#define VR_0     401
#define VR_1     402
#define VR_2     403
#define VR_3     404
#define VR_4     405
#define VR_5     406
#define VR_6     407
#define VR_7     408
#define VR_8     409
#define VR_9     410

#define VR_10    411
#define VR_11    412
#define VR_12    413
#define VR_13    414
#define VR_14    415
#define VR_15    416
#define VR_16    417
#define VR_17    418
#define VR_18    419
#define VR_19    420

#define VR_20    421
#define VR_21    422
#define VR_22    423
#define VR_23    424
#define VR_24    425
#define VR_25    426
#define VR_26    427
#define VR_27    428
#define VR_28    429
#define VR_29    430

#define VR_30    431
#define VR_31    432
#define VR_32    433
#define VR_33    434
#define VR_34    435
#define VR_35    436
#define VR_36    437
#define VR_37    438
#define VR_38    439
#define VR_39    440

#define VR_40    441
#define VR_41    442
#define VR_42    443
#define VR_43    444
#define VR_44    445
#define VR_45    446
#define VR_46    447
#define VR_47    448
#define VR_48    449
#define VR_49    450

//-------------------------->The Object Id for AR Devices (451-->500)<--------------------------------
#define AR_0     451
#define AR_1     452
#define AR_2     453
#define AR_3     454
#define AR_4     455
#define AR_5     456
#define AR_6     457
#define AR_7     458
#define AR_8     459
#define AR_9     460

#define AR_10    461
#define AR_11    462
#define AR_12    463
#define AR_13    464
#define AR_14    465
#define AR_15    466
#define AR_16    467
#define AR_17    468
#define AR_18    469
#define AR_19    470

#define AR_20    471
#define AR_21    472
#define AR_22    473
#define AR_23    474
#define AR_24    475
#define AR_25    476
#define AR_26    477
#define AR_27    478
#define AR_28    479
#define AR_29    480

#define AR_30    481
#define AR_31    482
#define AR_32    483
#define AR_33    484
#define AR_34    485
#define AR_35    486
#define AR_36    487
#define AR_37    488
#define AR_38    489
#define AR_39    490

#define AR_40    491
#define AR_41    492
#define AR_42    493
#define AR_43    494
#define AR_44    495
#define AR_45    496
#define AR_46    497
#define AR_47    498
#define AR_48    499
#define AR_49    500

//-------------------------->The Object Id for MR Devices (501-->550)<--------------------------------

#define MR_0     501
#define MR_1     502
#define MR_2     503
#define MR_3     504
#define MR_4     505
#define MR_5     506
#define MR_6     507
#define MR_7     508
#define MR_8     509
#define MR_9     510

#define MR_10    511
#define MR_11    512
#define MR_12    513
#define MR_13    514
#define MR_14    515
#define MR_15    516
#define MR_16    517
#define MR_17    518
#define MR_18    519
#define MR_19    520

#define MR_20    521
#define MR_21    522
#define MR_22    523
#define MR_23    524
#define MR_24    525
#define MR_25    526
#define MR_26    527
#define MR_27    528
#define MR_28    529
#define MR_29    530

#define MR_30    531
#define MR_31    532
#define MR_32    533
#define MR_33    534
#define MR_34    535
#define MR_35    536
#define MR_36    537
#define MR_37    538
#define MR_38    539
#define MR_39    540

#define MR_40    541
#define MR_41    542
#define MR_42    543
#define MR_43    544
#define MR_44    545
#define MR_45    546
#define MR_46    547
#define MR_47    548
#define MR_48    549
#define MR_49    550

//-------------------------->The Object Id for Global Server (551-->600)<--------------------------------

#define Gloal_Server_0  551
#define Gloal_Server_1  552
#define Gloal_Server_2  553
#define Gloal_Server_3  554
#define Gloal_Server_4  555
#define Gloal_Server_5  556
#define Gloal_Server_6  557
#define Gloal_Server_7  558
#define Gloal_Server_8  559
#define Gloal_Server_9  560

#define Gloal_Server_10 561
#define Gloal_Server_11 562
#define Gloal_Server_12 563
#define Gloal_Server_13 564
#define Gloal_Server_14 565
#define Gloal_Server_15 566
#define Gloal_Server_16 567
#define Gloal_Server_17 568
#define Gloal_Server_18 569
#define Gloal_Server_19 570

#define Gloal_Server_20 571
#define Gloal_Server_21 572
#define Gloal_Server_22 573
#define Gloal_Server_23 574
#define Gloal_Server_24 575
#define Gloal_Server_25 576
#define Gloal_Server_26 577
#define Gloal_Server_27 578
#define Gloal_Server_28 579
#define Gloal_Server_29 580

#define Gloal_Server_30 581
#define Gloal_Server_31 582
#define Gloal_Server_32 583
#define Gloal_Server_33 584
#define Gloal_Server_34 585
#define Gloal_Server_35 586
#define Gloal_Server_36 587
#define Gloal_Server_37 588
#define Gloal_Server_38 589
#define Gloal_Server_39 590

#define Gloal_Server_40 591
#define Gloal_Server_41 592
#define Gloal_Server_42 593
#define Gloal_Server_43 594
#define Gloal_Server_44 595
#define Gloal_Server_45 596
#define Gloal_Server_46 597
#define Gloal_Server_47 598
#define Gloal_Server_48 599
#define Gloal_Server_49 600
//-------------------------->The Object Id for Local Server (600-->650)<--------------------------------
#define Local_Server_0 601
#define Local_Server_1 602
#define Local_Server_2 603
#define Local_Server_3 604
#define Local_Server_4 605
#define Local_Server_5 606
#define Local_Server_6 607
#define Local_Server_7 608
#define Local_Server_8 609
#define Local_Server_9 610

#define Local_Server_10 611
#define Local_Server_11 612
#define Local_Server_12 613
#define Local_Server_13 614
#define Local_Server_14 615
#define Local_Server_15 616
#define Local_Server_16 617
#define Local_Server_17 618
#define Local_Server_18 619
#define Local_Server_19 620

#define Local_Server_20 621
#define Local_Server_21 622
#define Local_Server_22 623
#define Local_Server_23 624
#define Local_Server_24 625
#define Local_Server_25 626
#define Local_Server_26 627
#define Local_Server_27 628
#define Local_Server_28 629
#define Local_Server_29 630

#define Local_Server_30 631
#define Local_Server_31 632
#define Local_Server_32 633
#define Local_Server_33 634
#define Local_Server_34 635
#define Local_Server_35 636
#define Local_Server_36 637
#define Local_Server_37 638
#define Local_Server_38 639
#define Local_Server_39 640

#define Local_Server_40 641
#define Local_Server_41 642
#define Local_Server_42 643
#define Local_Server_43 644
#define Local_Server_44 645
#define Local_Server_45 646
#define Local_Server_46 647
#define Local_Server_47 648
#define Local_Server_48 649
#define Local_Server_49 650


//-------------------------The Object ID to Test-------------------------------------------

#define Local_Server 0
#define Vr_Server 1
#define Cloud_Server 3
#define Dt_Object 4

/*
 * ==========================> Define MessageDate Format By using Data Structure <======================
*/

//-------------------------->Transfer Packet Format<-----------------------------------------
struct IotMessage
{
  int TargetID;
  int SourceID;
  int MessageID;
  string MessageData;
  double TimeStamp;
  XTOSTRUCT(O(TargetID,SourceID,MessageID,MessageData,TimeStamp));
};

//-------------------------->MessageData ROS Format<---------------------------------------------

struct BoolMessage
{
  bool data;
  XTOSTRUCT(O(data));
};

struct MultiBoolMessage
{
  vector<bool> data;
  XTOSTRUCT(O(data));
};

struct FloatMessage
{
  float data;
  XTOSTRUCT(O(data));
};

struct MultiFloatMessage
{
  vector<float> data;
  XTOSTRUCT(O(data));
};

struct DoubleMessage
{
  double data;
  XTOSTRUCT(O(data));
};

struct MultiDoubleMessage
{
  vector<double> data;
  XTOSTRUCT(O(data));
};

struct StringMessage
{
  string data;
  XTOSTRUCT(O(data));
};

struct MultiStringMessage
{
  vector<string> data;
  XTOSTRUCT(O(data));
};

struct IntMessage
{
  int data;
  XTOSTRUCT(O(data));
};

struct MultiIntMessage
{
  vector<int> data;
  XTOSTRUCT(O(data));
};

struct Vector3Message
{
  double x;
  double y;
  double z;
  XTOSTRUCT(O(x,y,z));
};

struct AccelMessage
{
  double linear_x;
  double linear_y;
  double linear_z;
  double angular_x;
  double angular_y;
  double angular_z;
  XTOSTRUCT(O(linear_x,linear_y,linear_z,angular_x,angular_y,angular_z));
};

struct AccelWithCovarianceMessage
{
  double linear_x;
  double linear_y;
  double linear_z;
  double angular_x;
  double angular_y;
  double angular_z;
  vector<double> covariance;//64
  XTOSTRUCT(O(linear_x,linear_y,linear_z,angular_x,angular_y,angular_z,covariance));
};

struct InertiaMessage
{
  double m;
  double com_x;
  double com_y;
  double com_z;
  double ixx;
  double ixy;
  double ixz;
  double iyy;
  double iyz;
  double izz;
  XTOSTRUCT(O(m,com_x,com_y,com_z,ixx,ixy,ixz,iyy,iyz,izz));
};

struct PointMessage
{
  double x;
  double y;
  double z;
  XTOSTRUCT(O(x,y,z));
};

struct PolygonMessage
{
  vector<double> points_x;
  vector<double> points_y;
  vector<double> points_z;
  XTOSTRUCT(O(points_x,points_y,points_z));
};

struct QuaternionMessage
{
  double x;
  double y;
  double z;
  double w;
  XTOSTRUCT(O(x,y,z,w));
};

struct PoseMessage
{
  double position_x;
  double position_y;
  double position_z;
  double orientation_x;
  double orientation_y;
  double orientation_z;
  double orientation_w;
  XTOSTRUCT(O(position_x,position_y,position_z,orientation_x,orientation_y,orientation_z,orientation_w));
};

struct Pose2DMessage
{
  double x;
  double y;
  double theta;
  XTOSTRUCT(O(x,y,theta));
};

struct PoseArrayMessage
{
  vector<double> positions_x;
  vector<double> positions_y;
  vector<double> positions_z;
  vector<double> orientations_x;
  vector<double> orientations_y;
  vector<double> orientations_z;
  vector<double> orientations_w;
  XTOSTRUCT(O(positions_x,positions_y,positions_z,orientations_x,orientations_y,orientations_z,orientations_w));
};

struct PoseWithCovarianceMessage
{
  double position_x;
  double position_y;
  double position_z;
  double orientation_x;
  double orientation_y;
  double orientation_z;
  double orientation_w;
  vector<double> covariance;
  XTOSTRUCT(O(position_x,position_y,position_z,orientation_x,orientation_y,orientation_z,orientation_w,covariance));
};

struct TransformMessage
{
  double translation_x;
  double translation_y;
  double translation_z;
  double rotation_x;
  double rotation_y;
  double rotation_z;
  double rotation_w;
  XTOSTRUCT(O(translation_x,translation_y,translation_z,rotation_x,rotation_y,rotation_z,rotation_w));
};

struct TwistMessage
{
  double linear_x;
  double linear_y;
  double linear_z;
  double angular_x;
  double angular_y;
  double angular_z;
  XTOSTRUCT(O(linear_x,linear_y,linear_z,angular_x,angular_y,angular_z));
};

struct TwistWithCovarianceMessage
{
  double linear_x;
  double linear_y;
  double linear_z;
  double angular_x;
  double angular_y;
  double angular_z;
  vector<double> covariance;
  XTOSTRUCT(O(linear_x,linear_y,linear_z,angular_x,angular_y,angular_z,covariance));
};

struct WrenchMessage
{
  double force_x;
  double force_y;
  double force_z;
  double torque_x;
  double torque_y;
  double torque_z;
  XTOSTRUCT(O(force_x,force_y,force_z,torque_x,torque_y,torque_z));
};

struct BatteryStateMessage
{
  double voltage;
  double temperature;
  double current;
  double charge;
  double capacity;
  double design_capacity;
  double percentage;
  int    power_supply_status;
  int    power_supply_health;
  int    power_supply_technology;
  bool   persent;
  vector<double> cell_voltage;
  vector<double> cell_temperature;
  string location;
  string serial_number;
  XTOSTRUCT(O(voltage,temperature,current,charge,capacity,design_capacity,percentage,power_supply_status,power_supply_health,power_supply_technology,persent,cell_voltage,cell_temperature,location,serial_number));
};

struct CameraInfoMessage
{
  int height;
  int width;
  string distortion_model;
  vector<double> D;
  vector<double> K;
  vector<double> R;
  vector<double> F;
  XTOSTRUCT(O(height,width,distortion_model,D,K,R,F));
};

struct ChannelFloatMessage
{
  string name;
  vector<float> values;
  XTOSTRUCT(O(name,values));
};

struct CompressedImageMessage
{
  string format;//jpeg png
  vector<int> data;
  XTOSTRUCT(O(format,data));
};

struct FluidPressureMessage
{
  double fluid_pressure;
  double variance;
  XTOSTRUCT(O(fluid_pressure,variance));
};

struct IlluminanceMessage
{
  double illuminance;
  double variance;
  XTOSTRUCT(O(illuminance,variance));
};

struct ImageMessage
{
  int height;
  int width;
  string encoding;
  int is_bigendian;
  int step;
  vector<int> data;
  XTOSTRUCT(O(height,width,encoding,is_bigendian,step,data));
};

struct ImuMessage
{
  double orientation_x;
  double orientation_y;
  double orientation_z;
  double orientation_w;
  vector<double> orientation_covariance;
  double angular_velocity_x;
  double angular_velocity_y;
  double angular_velocity_z;
  vector<double> angular_velocity_covariance;
  double linear_acceleration_x;
  double linear_acceleration_y;
  double linear_acceleration_z;
  vector<double> linear_acceleration_covariance;
  XTOSTRUCT(O(orientation_x,orientation_y,orientation_z,orientation_w,orientation_covariance,angular_velocity_x,angular_velocity_y,angular_velocity_z,angular_velocity_covariance,linear_acceleration_x,linear_acceleration_y,linear_acceleration_z,linear_acceleration_covariance));
};

struct JointStateMessage
{
  vector<string> name;
  vector<double> position;
  vector<double> velocity;
  vector<double> effort;
  XTOSTRUCT(O(name,position,velocity,effort));
};

struct JoyMessage
{
  vector<double> axes;
  vector<double> buttons;
  XTOSTRUCT(O(axes,buttons));
};

struct JoyFeedbackMessage
{
  int type;
  int id;
  double intensity;
  XTOSTRUCT(O(type,id,intensity));
};

struct JoyFeedbackArrayMessage
{
  vector<int> types;
  vector<int> ids;
  vector<double> intensities;
  XTOSTRUCT(O(types,ids,intensities));
};

struct LaserEchoMessage
{
  vector<double> echoes;
  XTOSTRUCT(O(echoes));
};

struct LaserScanMessage
{
  float angle_min;
  float angle_max;
  float angle_increment;
  float time_increment;
  float scan_time;
  float range_min;
  float range_max;
  vector<float> ranges;
  vector<float> intensities;
  XTOSTRUCT(O(angle_min,angle_max,angle_increment,time_increment,scan_time,range_min,range_max,ranges,intensities));
};

struct MagneticFieldMessage
{
  double magnetic_field_x;
  double magnetic_field_y;
  double magnetic_field_z;
  vector<double> magnetic_field_covariance;
  XTOSTRUCT(O(magnetic_field_x,magnetic_field_y,magnetic_field_z,magnetic_field_covariance));
};

struct MultiDOFJointStateMessage
{
  vector<string> joint_names;
  vector<double> transforms_translation_x;
  vector<double> transforms_translation_y;
  vector<double> transforms_translation_z;
  vector<double> transforms_rotation_x;
  vector<double> transforms_rotation_y;
  vector<double> transforms_rotation_z;
  vector<double> transforms_rotation_w;
  vector<double> twist_linear_x;
  vector<double> twist_linear_y;
  vector<double> twist_linear_z;
  vector<double> twist_angular_x;
  vector<double> twist_angular_y;
  vector<double> twist_angular_z;
  vector<double> wrench_force_x;
  vector<double> wrench_force_y;
  vector<double> wrench_force_z;
  vector<double> wrench_torque_x;
  vector<double> wrench_torque_y;
  vector<double> wrench_torque_z;
  XTOSTRUCT(O(joint_names,transforms_translation_x,transforms_translation_y,transforms_translation_z,transforms_rotation_x,transforms_rotation_y,transforms_rotation_z,transforms_rotation_w,twist_linear_x,
              twist_linear_y,twist_linear_z,twist_angular_x,twist_angular_y,twist_angular_z,wrench_force_x,wrench_force_y,wrench_force_z,wrench_torque_x,wrench_torque_y,wrench_torque_z));
};

struct MultiEchoLaserScanMessage
{
  float angle_min;
  float angle_max;
  float angle_increment;
  float time_increment;
  float scan_time;
  float range_min;
  float range_max;
  vector<vector<double> > ranges;
  vector<vector<double> > intensities;
  XTOSTRUCT(O(angle_min,angle_max,angle_increment,time_increment,scan_time,range_min,range_max,ranges,intensities));
};

struct NavSatStatusMessage
{
  int status;
  int service;
  XTOSTRUCT(O(status,service));
};

struct NavSatFixMessage
{
  int status;
  int service;
  double latitude;
  double longitude;
  double altitude;
  vector<double> position_covariance;
  int position_covariance_type;
  XTOSTRUCT(O(status,service,latitude,longitude,altitude,position_covariance,position_covariance_type));
};

struct PointCloudMessage
{
  double points_x;
  double points_y;
  double points_z;
  vector<string> channels_names;
  vector<vector<float> > channels_values;
  XTOSTRUCT(O(points_x,points_y,points_z,channels_names,channels_values));
};

struct PointCloud2Message
{
  int height;
  int width;
  vector<string> fields_name;
  vector<int> fields_offset;
  vector<int> fields_datatype;
  vector<int> fields_count;
  bool is_bigendian;
  int point_step;
  int row_step;
  vector<int> data;
  bool is_dense;
  XTOSTRUCT(O(height,width,fields_name,fields_offset,fields_datatype,fields_count,is_bigendian,point_step,row_step,data,is_dense));
};

struct PointFieldMessage
{
  string name;
  int offset;
  int datatype;
  int count;
  XTOSTRUCT(O(name,offset,datatype,count));
};

struct RangeMessage
{
  int radiation_type;
  float field_of_view;
  float min_range;
  float max_range;
  float range;
  XTOSTRUCT(O(radiation_type,field_of_view,min_range,max_range,range));
};

struct RegionOfInterestMessage
{
  int x_offset;
  int y_offset;
  int height;
  int width;
  bool do_rectify;
  XTOSTRUCT(O(x_offset,y_offset,height,width,do_rectify));
};

struct RelativeHumidityMessage
{
  double relative_humidity;
  double variance;
  XTOSTRUCT(O(relative_humidity,variance));
};

struct TemperatureMessage
{
  double temperature;
  double variance;
  XTOSTRUCT(O(temperature,variance));
};

struct TimeReferenceMessage
{
  long time_ref;
  string source;
  XTOSTRUCT(O(time_ref,source));
};

struct GridCellsMessage
{
  float cell_width;
  float cell_height;
  vector<double> cells_x;
  vector<double> cells_y;
  vector<double> cells_z;
  XTOSTRUCT(O(cell_width,cell_height,cells_x,cells_y,cells_z));
};

struct MapMetaDataMessage
{
  long map_load_time;
  float resolution;
  int width;
  int height;
  double origin_position_x;
  double origin_position_y;
  double origin_position_z;
  double origin_orientation_x;
  double origin_orientation_y;
  double origin_orientation_z;
  double origin_orientation_w;
  XTOSTRUCT(O(map_load_time,resolution,width,height,origin_position_x,origin_position_y,origin_position_z,origin_orientation_x,origin_orientation_y,origin_orientation_z,origin_orientation_w));
};

struct OccupancyGridMessage
{
  long map_load_time;
  float resolution;
  int width;
  int height;
  double origin_position_x;
  double origin_position_y;
  double origin_position_z;
  double origin_orientation_x;
  double origin_orientation_y;
  double origin_orientation_z;
  double origin_orientation_w;
  vector<int> data;
  XTOSTRUCT(O(map_load_time,resolution,width,height,origin_position_x,origin_position_y,origin_position_z,origin_orientation_x,origin_orientation_y,origin_orientation_z,origin_orientation_w,data));
};

struct OdometryMessage
{
  string child_frame_id;
  double pose_pose_position_x;
  double pose_pose_position_y;
  double pose_pose_position_z;
  double pose_pose_orientation_x;
  double pose_pose_orientation_y;
  double pose_pose_orientation_z;
  double pose_pose_orientation_w;
  vector<double> pose_covariance;
  double twist_twist_linear_x;
  double twist_twist_linear_y;
  double twist_twist_linear_z;
  double twist_twist_angular_x;
  double twist_twist_angular_y;
  double twist_twist_angular_z;
  vector<double> twist_covariance;
  XTOSTRUCT(O(child_frame_id,pose_pose_position_x,pose_pose_position_y,pose_pose_position_z,pose_pose_orientation_z,pose_pose_orientation_y,pose_pose_orientation_x,pose_pose_orientation_w,pose_covariance,twist_twist_linear_x,twist_twist_linear_y,twist_twist_linear_z,twist_twist_angular_x,twist_twist_angular_y,twist_twist_angular_z,twist_covariance));
};

struct PathMessage
{
  vector<double> pose_position_x;
  vector<double> pose_position_y;
  vector<double> pose_position_z;
  vector<double> pose_orientation_x;
  vector<double> pose_orientation_y;
  vector<double> pose_orientation_z;
  vector<double> pose_orientation_w;
  XTOSTRUCT(O(pose_position_x,pose_position_y,pose_position_z,pose_orientation_x,pose_orientation_y,pose_orientation_z,pose_orientation_w));
};

struct GetMapMessage
{
  long map_load_time;
  float resolution;
  int width;
  int height;
  double origin_position_x;
  double origin_position_y;
  double origin_position_z;
  double origin_orientation_x;
  double origin_orientation_y;
  double origin_orientation_z;
  double origin_orientation_w;
  vector<int> data;
  XTOSTRUCT(O(map_load_time,resolution,width,height,origin_position_x,origin_position_y,origin_position_z,origin_orientation_x,origin_orientation_y,origin_orientation_z,origin_orientation_w,data));
};

struct GetPlanMessage
{
  double start_pose_position_x;
  double start_pose_position_y;
  double start_pose_position_z;
  double start_pose_orientation_x;
  double start_pose_orientation_y;
  double start_pose_orientation_z;
  double start_pose_orientation_w;

  double goal_pose_position_x;
  double goal_pose_position_y;
  double goal_pose_position_z;
  double goal_pose_orientation_x;
  double goal_pose_orientation_y;
  double goal_pose_orientation_z;
  double goal_pose_orientation_w;

  float tolerance;

  vector<double> pose_position_x;
  vector<double> pose_position_y;
  vector<double> pose_position_z;
  vector<double> pose_orientation_x;
  vector<double> pose_orientation_y;
  vector<double> pose_orientation_z;
  vector<double> pose_orientation_w;

  XTOSTRUCT(O(start_pose_position_x,start_pose_position_y,start_pose_position_z,start_pose_orientation_x,start_pose_orientation_y,start_pose_orientation_z,start_pose_orientation_w,
              goal_pose_position_x,goal_pose_position_y,goal_pose_position_z,goal_pose_orientation_x,goal_pose_orientation_y,goal_pose_orientation_z,goal_pose_orientation_w,tolerance,pose_position_x,pose_position_y,pose_position_z,pose_orientation_x,pose_orientation_y,pose_orientation_z,pose_orientation_w));
};

struct LoadMapMessage
{
  string map_url;
  int result;

  long map_load_time;
  float resolution;
  int width;
  int height;
  double origin_position_x;
  double origin_position_y;
  double origin_position_z;
  double origin_orientation_x;
  double origin_orientation_y;
  double origin_orientation_z;
  double origin_orientation_w;
  vector<int> data;
  XTOSTRUCT(O(map_load_time,resolution,width,height,origin_position_x,origin_position_y,origin_position_z,origin_orientation_x,origin_orientation_y,origin_orientation_z,origin_orientation_w,data,map_url,result));
};

//--------------------------------------------------->Message Data ID <-----------------------------------
#define BoolMessageID                              0
#define MultiBoolMessageID                         1
#define FloatMessageID                             2
#define MultiFloatMessageID                        3
#define DoubleMessageID                            4
#define MultiDoubleMessageID                       5
#define StringMessageID                            6
#define MultiStringMessageID                       7
#define IntMessageID                               8
#define MultiIntMessageID                          9
#define Vector3MessageID                           10
#define AccelMessageID                             11
#define AccelWithCovarianceMessageID               12
#define InertiaMessageID                           13
#define PointMessageID                             14
#define PolygonMessageID                           15
#define QuaternionMessageID                        16
#define PoseMessageID                              17
#define Pose2DMessageID                            18
#define PoseArrayMessageID                         19
#define PoseWithCovarianceMeID                     20
#define TransformMessageID                         21
#define TwistMessageID                             22
#define TwistWithCovarianceMessageID               23
#define WrenchMessageID                            24
#define BatteryStateMessageID                      25
#define CameraInfoMessageID                        26
#define ChannelFloatMessageID                      27
#define CompressedImageMessageID                   28
#define FluidPressureMessageID                     29
#define IlluminanceMessageID                       30
#define ImageMessageID                             31
#define ImuMessageID                               32
#define JointStateMessageID                        33
#define JoyMessageID                               34
#define JoyFeedbackMessageID                       35
#define JoyFeedbackArrayMessageID                  36
#define LaserEchoMessageID                         37
#define LaserScanMessageID                         38
#define MagneticFieldMessageID                     39
#define MultiDOFJointStateMessageID                40
#define MultiEchoLaserScanMessageID                41
#define NavSatStatusMessageID                      42
#define NavSatFixMessageID                         43
#define PointCloudMessageID                        44
#define PointCloud2MessageID                       45
#define PointFieldMessageID                        46
#define RangeMessageID                             47
#define RegionOfInterestMessageID                  48
#define RelativeHumidityMessageID                  49
#define TemperatureMessageID                       50
#define TimeReferenceMessageID                     51
#define GridCellsMessageID                         52
#define MapMetaDataMessageID                       53
#define OccupancyGridMessageID                     54
#define OdometryMessageID                          55
#define PathMessageID                              56
#define GetMapMessageID                            57
#define GetPlanMessageID                           58
#define LoadMapMessageID                           59

//---------------------------------->Object Message Data && MessageID<-------------------------------
//---------------------------------->Uav Object<-----------------------------------------------------
#define UavCurrentPoseMessageID   101
struct UavCurrentPoseMessage
{
  double position_x;
  double position_y;
  double position_z;
  double rotation_x;
  double rotation_y;
  double rotation_z;
  double rotation_w;
  XTOSTRUCT(O(position_x,position_y,position_z,rotation_x,rotation_y,rotation_z,rotation_w));
};

#define UavRefPoseMessageID       102
struct UavRefPoseMessage
{
  double position_x;
  double position_y;
  double position_z;
  double rotation_x;
  double rotation_y;
  double rotation_z;
  double rotation_w;
  XTOSTRUCT(O(position_x,position_y,position_z,rotation_x,rotation_y,rotation_z,rotation_z,rotation_w));
};

#define UavCurrentVelocityMessageID  103
struct UavCurrentVelocityMessage
{
  double linear_velocity_x;
  double linear_velocity_y;
  double linear_velocity_z;
  double anger_velocity_x;
  double anger_velocity_y;
  double anger_velocity_z;
  XTOSTRUCT(O(linear_velocity_x,linear_velocity_y,linear_velocity_z,anger_velocity_x,anger_velocity_y,anger_velocity_z));
};

#define UavRefVelocityMessageID     104
struct UavRefVelocityMessage
{
  double linear_velocity_x;
  double linear_velocity_y;
  double linear_velocity_z;
  double anger_velocity_x;
  double anger_velocity_y;
  double anger_velocity_z;
  XTOSTRUCT(O(linear_velocity_x,linear_velocity_y,linear_velocity_z,anger_velocity_x,anger_velocity_y,anger_velocity_z));
};

#define UavStartMessageID  105
struct UavStartMessage
{
  bool start;
  XTOSTRUCT(O(start));
};

#define UavGlobalPositionMessageID  106
struct UavGlobalPositionMessage
{
  int status;
  int service;
  double latitude;
  double longitude;
  double altitude;
  vector<double> position_covariance;//9
  int position_covariance_type;
  XTOSTRUCT(O(status,service,latitude,longitude,altitude,position_covariance,position_covariance_type));
};

#define UavLocalPositionMessageID  107
struct UavLocalPositionMessage
{
  double position_x;
  double position_y;
  double position_z;
  double rotation_x;
  double rotation_y;
  double rotation_z;
  double rotation_w;
  XTOSTRUCT(O(position_x,position_y,position_z,rotation_x,rotation_y,rotation_z,rotation_w));
};

#define UavLocalVelocityMessageID  108
struct UavLocalVelocityMessage
{
  double linear_velocity_x;
  double linear_velocity_y;
  double linear_velocity_z;
  double anger_velocity_x;
  double anger_velocity_y;
  double anger_velocity_z;
  XTOSTRUCT(O(linear_velocity_x,linear_velocity_y,linear_velocity_z,anger_velocity_x,anger_velocity_y,anger_velocity_z));
};
#define UavCompressedImageMessagID 109
struct UavCompressedImageMessage
{
  string format;//jpeg png
  vector<int> data;
  XTOSTRUCT(O(format,data));
};

#define VUavGlobalPositionMessageID  110
struct VUavGlobalPositionMessage
{
  double position_x;
  double position_y;
  double position_z;
  double rotation_x;
  double rotation_y;
  double rotation_z;
  double rotation_w;
  XTOSTRUCT(O(position_x,position_y,position_z,rotation_x,rotation_y,rotation_z,rotation_w));
};


#define TimeSycSendMessageID 111
struct TimeSycSendMessage
{
  int SourceID;
  int TargetID;
  double t1;
  XTOSTRUCT(O(SourceID,TargetID,t1));
};

#define TimeSycBackMessageID 112
struct TimeSycBackMessage
{
  int SourceID;
  int TargetID;
  double t1;
  double t2;
  double t3;
  XTOSTRUCT(O(SourceID,TargetID,t1,t2,t3));
};

#define TimeSycInforMessageID 113
struct TimeSycInforMessage
{
  int SourceID;
  int TargetID;
  double transfor_delay;
  double system_delay;
  XTOSTRUCT(O(SourceID,TargetID,transfor_delay,system_delay));
};


#define DelayTimeTestMessageID 114
struct DelayTimeTestMessage
{
  double position_x;
  double position_y;
  double position_z;
  double rotation_x;
  double rotation_y;
  double rotation_z;
  double rotation_w;
  double sys_time;
  XTOSTRUCT(O(position_x,position_y,position_z,rotation_w,rotation_x,rotation_y,rotation_z,sys_time));
};

#define UavRunSpanPoseMessageID 115
struct UavRunSpanPoseMessage
{
  double span_x;
  double span_y;
  double span_z;
  XTOSTRUCT(O(span_x,span_y,span_z));
};
#define MrCommandMessageID 116
struct MrCommandMessage
{
  float mode;
  float LinearVelocityX;
  float LinearVelocityY;
  float LinearVelocityZ;
  double Latitude;
  double Longitude;
  double Altitude;
  float SpatialPositionX;
  float SpatialPositionY;
  float SpatialPositionZ;
  XTOSTRUCT(O(mode,LinearVelocityX,LinearVelocityY,LinearVelocityZ,Latitude,Longitude,Altitude,SpatialPositionX,SpatialPositionY,SpatialPositionZ));
};

#define HitMessageID     1000
struct HitMessage
{
  bool isHit;
  XTOSTRUCT(O(isHit));
};

#define UavStateMsgID   1200
struct UavStateMsg
{
  bool connected;
  bool armed;
  bool guided;
  bool manual_input;
  string mode;
  uint system_status;
  XTOSTRUCT(O(connected,armed,guided,manual_input,mode,system_status));
};




//=======================================================================================================================
//=============================> Define Message Format V2 <===============================
//=======================================================================================================================
#define CurrentLocalPositionMsgID 1
struct CurrentLocalPositionMsg
{
  double position_x;
  double position_y;
  double position_z;
  double rotation_x;
  double rotation_y;
  double rotation_z;
  double rotation_w;
  XTOSTRUCT(O(position_x,position_y,position_z,rotation_w,rotation_x,rotation_y,rotation_z));
};

#define CurrentGlobalPositionMsgID 2
struct CurrentGlobalPositionMsg
{
  double latitude;
  double longitude;
  double altitude;
  XTOSTRUCT(O(latitude,longitude,altitude));
};

#define CurrentVelocityMsgID 3
struct CurrentVelocityMsg
{
  double linear_velocity_x;
  double linear_velocity_y;
  double linear_velocity_z;
  double anger_velocity_x;
  double anger_velocity_y;
  double anger_velocity_z;
  XTOSTRUCT(O(linear_velocity_x,linear_velocity_y,linear_velocity_z,anger_velocity_x,anger_velocity_y,anger_velocity_z));
};

#define CurrentStateMsgID  4
struct CurrentStateMsg
{
  bool connected;
  bool armed;
  bool guided;
  bool manual_input;
  string mode;
  uint system_status;
  XTOSTRUCT(O(connected,armed,guided,manual_input,mode,system_status));
};

#define TargetLocalPositionMsgID 11
struct TargetLocalPositionMsg
{
  double position_x;
  double position_y;
  double position_z;
  double rotation_x;
  double rotation_y;
  double rotation_z;
  double rotation_w;
  XTOSTRUCT(O(position_x,position_y,position_z,rotation_w,rotation_x,rotation_y,rotation_z));
};

#define TargetGlobalPositionMsgID 12
struct TargetGlobalPositionMsg
{
  double latitude;
  double longitude;
  double altitude;
  XTOSTRUCT(O(latitude,longitude,altitude));
};

#define TargetVelocityMsgID 13
struct TargetVelocityMsg
{
  double linear_velocity_x;
  double linear_velocity_y;
  double linear_velocity_z;
  double anger_velocity_x;
  double anger_velocity_y;
  double anger_velocity_z;
  XTOSTRUCT(O(linear_velocity_x,linear_velocity_y,linear_velocity_z,anger_velocity_x,anger_velocity_y,anger_velocity_z));
};

#define TargetCmdTypeMsgID 14
struct TargetCmdTypeMsg
{
  int type;
  XTOSTRUCT(O(type));
};

#define ControlApplyMsgID 15
struct ControlApplyMsg
{
  bool apply_info;
  XTOSTRUCT(O(apply_info));
};

}
#endif // DEFINE_COMMON_H
