#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum HandType {
    HIGH,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND,

    HANDTYPE_COUNT
};

struct Hand {
    char hand[5];
    int bid;
    HandType type;
};

int get_card_id(char c) {
    char cards[] = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
    for (int i = 0; i < 13; ++i) {
        if (c == cards[i])
            return i;
    }

    return 0;
}

HandType get_hand_type(char* c) {
    int counts[13] = {0};
    for (int i = 0; i < 5; ++i) {
        int id = get_card_id(c[i]);
        counts[id]++;
    }

    int pairs = 0;
    for (int i = 0; i < 13; ++i) {
        if (counts[i] == 5)
            return FIVE_OF_A_KIND;
        if (counts[i] == 4)
            return FOUR_OF_A_KIND;
        if (counts[i] == 3) {
            for (int j = 0; j < 13; ++j) {
                if (counts[j] == 2)
                    return FULL_HOUSE;
            }
            return THREE_OF_A_KIND;
        }
        if (counts[i] == 2)
            pairs++;
    }

    if (pairs == 2)
        return TWO_PAIR;
    if (pairs == 1)
        return ONE_PAIR;

    return HIGH;
}

int main()
{
    FILE* fp = fopen("input.txt", "r");
    char line[1024];
    Hand hands[1024];
    int hand_count = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        char* hand_str = strtok(line, " ");
        char* bid_str = strtok(NULL, " ");
        Hand hand;
        memcpy(hand.hand, hand_str, 5);
        hand.bid = atoi(bid_str);
        hand.type = get_hand_type(hand_str);

        int add_idx = hand_count;
        for (int i = 0; i < hand_count; ++i) {
            if (hand.type < hands[i].type) {
                add_idx = i;
                goto complete;
            } else if (hand.type == hands[i].type) {
                for (int c = 0; c < 5; ++c) {
                    int c0 = get_card_id(hand.hand[c]);
                    int c1 = get_card_id(hands[i].hand[c]);
                    if (c0 == c1)
                        continue;
                    if (c0 > c1)
                        break;

                    add_idx = i;
                    goto complete;
                }
            }
        }

complete:
        if (add_idx < hand_count) {
            int remaining = hand_count - add_idx;
            memcpy(hands + add_idx + 1, hands + add_idx, sizeof(Hand) * remaining);
        }
        hands[add_idx] = hand;
        hand_count++;
    }

    int total = 0;
    for (int i = 0; i < hand_count; ++i) {
        total += hands[i].bid * (i + 1);
    }

    printf("answer: %d\n", total);
}
