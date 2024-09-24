#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to encode the PIN
char *encode_pin(const char *pin) {
  static char encoded_pin[5]; // Buffer for encoded PIN
  for (int i = 0; i < 4; i++) {
    // Add 5 to each character, with wraparound
    int sum = pin[i] - '0' + 5;
    encoded_pin[i] = (sum % 10) + '0'; // Get the last digit
    if (sum > 9) {
      encoded_pin[i] += sum / 10; // Add the remaining value to '0'
    }
  }
  encoded_pin[4] = '\0'; // Null-terminate the string
  return encoded_pin;
}

// Function to decode the encoded PIN
char* decode_pin(const char* encoded_pin) {
    static char decoded_pin[5]; // Buffer for decoded PIN
    for (int i = 0; i < 4; i++) {
        // Inverse of the encoding operation
        int digit = (encoded_pin[i] - '0' - 5);
        if (digit < 0) {
            digit += 10; // Handle negative values
        }
        decoded_pin[i] = digit + '0';
    }
    decoded_pin[4] = '\0'; // Null-terminate the string
    return decoded_pin;
}

char* decode_string(const char* encoded_str, const char* pin) {
    static char decoded_str[256]; // Buffer for decoded string
    int pin_len = strlen(pin);
    int str_len = strlen(encoded_str);
    for (int i = 0; i < str_len; i++) {
        int decoded_value = encoded_str[i] - pin[i % pin_len];
        if (decoded_value < 32 || decoded_value > 126) {
            decoded_value = (decoded_value - 32 + (127 - 32)) % (127 - 32) + 32;
        }
        decoded_str[i] = decoded_value;
    }
    decoded_str[str_len] = '\0'; // Null-terminate the string
    return decoded_str;
}

int main(int argc, char *argv[]) {
  // Check if the pin is provided as a command line argument
  if (argc != 2) {
    printf("Usage: %s <pin>\n", argv[0]);
    return 1;
  }

  // Decode the provided PIN
  char *decoded_pin = decode_pin(argv[1]);

  // Encode the provided PIN
//   char *encoded_provided_pin = encode_pin(argv[1]);
//   printf("Encoded Provided PIN: %s\n", encoded_provided_pin);

  // Encode the correct PIN
  char *correct_pin = "8446";
//   char *encoded_correct_pin = encode_pin(correct_pin);
//   printf("Encoded Correct PIN: %s\n", encoded_correct_pin);

//   printf("Decoded PIN: %s\n", decoded_pin);
//   printf("Correct PIN: %s\n", correct_pin);

  // Compare the decoded PIN with the correct PIN
  size_t provided_pin_length = strlen(argv[1]);
  size_t correct_pin_length = strlen(correct_pin);
  if (strncmp(decoded_pin, correct_pin, correct_pin_length) != 0 ||
      strlen(decoded_pin) != provided_pin_length) {
    printf("This is not right\n");
    return 1;
  }

  printf("Correct PIN entered!\n");
  char* encoded_string = "}|.wOlHtc}j@z9jf3 O Q";
  char* decoded_string = decode_string(encoded_string, argv[1]);
  printf("Decoded String: %s\n", decoded_string);
  return 0;
}