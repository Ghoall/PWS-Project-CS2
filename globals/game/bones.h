#pragma once
#include "../math.h"


//credits, asver
struct Bone;

void read_bones(uintptr_t m_pGameSceneNode, Bone& bones);

enum bones : int
{
    head = 6,
    neck = 5,
    spine = 4,
    spine_1 = 2,
    left_shoulder = 8,
    left_arm = 9,
    left_hand = 11,
    cock = 0,
    right_shoulder = 13,
    right_arm = 14,
    right_hand = 16,
    left_hip = 22,
    left_knee = 23,
    left_feet = 24,
    right_hip = 25,
    right_knee = 26,
    right_feet = 27
};

struct BoneConnection
{
    int bone1;
    int bone2;

    BoneConnection(int b1, int b2) : bone1(b1), bone2(b2) {}
};

inline BoneConnection boneConnections[] = {
    BoneConnection(6, 5),  // head to neck
    BoneConnection(5, 4),  // neck to spine
    BoneConnection(4, 0),  // spine to hip
    BoneConnection(4, 8), // spine to left shoulder
    BoneConnection(8, 9), // left shoulder to left arm
    BoneConnection(9, 11), // arm to hand
    BoneConnection(4, 13),
    BoneConnection(13, 14),
    BoneConnection(14, 16),
    BoneConnection(4, 2),  // spine to spine_1
    BoneConnection(0, 22), // hip to left_hip
    BoneConnection(0, 25), // hip to right_hip
    BoneConnection(22, 23), // left_hip to left_knee
    BoneConnection(23, 24), // left knee to left foot
    BoneConnection(25, 26), // right_hip to right_knee
    BoneConnection(26, 27) // right knee to right foot
};

struct Bone
{
    Vector3 Bone1;          // Bone position 1
    char pad_00[0x14];     // Padding for alignment

    Vector3 Bone2;          // Bone position 2
    char pad_01[0x14];     // Padding for alignment

    Vector3 Bone3;          // Bone position 3
    char pad_02[0x14];     // Padding for alignment

    Vector3 Bone4;          // Bone position 4
    char pad_03[0x14];     // Padding for alignment

    Vector3 Bone5;          // Bone position 5
    char pad_04[0x14];     // Padding for alignment

    Vector3 Bone6;          // Bone position 6
    char pad_05[0x14];     // Padding for alignment

    Vector3 Bone7;          // Bone position 7
    char pad_06[0x14];     // Padding for alignment

    Vector3 Bone8;          // Bone position 8
    char pad_07[0x14];     // Padding for alignment

    Vector3 Bone9;          // Bone position 9
    char pad_08[0x14];     // Padding for alignment

    Vector3 Bone10;         // Bone position 10
    char pad_09[0x14];     // Padding for alignment

    Vector3 Bone11;         // Bone position 11
    char pad_10[0x14];     // Padding for alignment

    Vector3 Bone12;         // Bone position 12
    char pad_11[0x14];     // Padding for alignment

    Vector3 Bone13;         // Bone position 13
    char pad_12[0x14];     // Padding for alignment

    Vector3 Bone14;         // Bone position 14
    char pad_13[0x14];     // Padding for alignment

    Vector3 Bone15;         // Bone position 15
    char pad_14[0x14];     // Padding for alignment

    Vector3 Bone16;         // Bone position 16
    char pad_15[0x14];     // Padding for alignment

    Vector3 Bone17;         // Bone position 17
    char pad_16[0x14];     // Padding for alignment

    Vector3 Bone18;         // Bone position 18
    char pad_17[0x14];     // Padding for alignment

    Vector3 Bone19;         // Bone position 19
    char pad_18[0x14];     // Padding for alignment

    Vector3 Bone20;         // Bone position 20
    char pad_19[0x14];     // Padding for alignment

    Vector3 Bone21;         // Bone position 21
    char pad_20[0x14];     // Padding for alignment

    Vector3 Bone22;         // Bone position 22
    char pad_21[0x14];     // Padding for alignment

    Vector3 Bone23;         // Bone position 23
    char pad_22[0x14];     // Padding for alignment

    Vector3 Bone24;         // Bone position 24
    char pad_23[0x14];     // Padding for alignment

    Vector3 Bone25;         // Bone position 25
    char pad_24[0x14];     // Padding for alignment

    Vector3 Bone26;         // Bone position 26
    char pad_25[0x14];     // Padding for alignment

    Vector3 Bone27;         // Bone position 27
    char pad_26[0x14];     // Padding for alignment

    Vector3 Bone28;         // Bone position 27
    char pad_27[0x14];     // Padding for alignment
};