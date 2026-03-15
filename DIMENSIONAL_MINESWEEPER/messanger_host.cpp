#include "common_code.cpp"
#include "users_data.cpp"

void Load_posts_data(ArrayUsers au) {
    FILE* f = nullptr;
    fopen_s(&f, "posts.txt", "rb");  // open the file for reading
    if (f == nullptr) {
        fclose(f);
        return;
    }

    int length = _filelength(_fileno(f)); // get the file length in bytes
    length = length / sizeof(Message);  // calculate the number of posts in the file

    if (length != 0) {
        au.CountMs = length;
        au.SizeMs = au.CountMs + au.Block;

        if (au.ptrMs != nullptr) {
            for (int i = 0; i < au.CountMs; i++) {
                delete au.ptrMs[i];
            }
            delete[] au.ptrMs; // free previous data
        }

        Message** temp = new Message*[au.SizeMs];
        au.ptrMs = temp;

        for (int i = 0; i < au.CountMs; i++) {  // read post data from the file
            fread(&au.ptrMs[i], sizeof(Message), 1, f);
        }
    } else {
        au.ptrMs = nullptr;
        au.SizeMs = 0;
        au.CountMs = 0;
    }
    fclose(f);
}

#include <iostream>
#include <cstring> // для strlen

using namespace std;

#include <iostream>
#include <cstring> // для strlen

using namespace std;

void Print_wrap_text(const char* text, int width, int tabulation = 0, int max_lines = -1) { // this function writen by GPT (i`m soo lazy for this)
    int len = strlen(text);
    int pos = 0;
    int line_count = 0;

    while (pos < len) {
        bool is_last_line = (max_lines > 0 && line_count + 1 == max_lines); // Check if this is the last line to print
        if (is_last_line && pos >= len) break; // If it's the last line

        while (pos < len && text[pos] == ' ') pos++; // Skip leading spaces

        int line_len = 0;
        int word_start = pos;
        int last_valid_end = pos;

        // Find the end of the current line
        while (pos < len) {
            int word_end = pos;
            while (word_end < len && text[word_end] != ' ') word_end++;

            int word_len = word_end - pos;
            int space_needed = (line_len > 0 ? 1 : 0);

            if (line_len + space_needed + word_len > width) break;

            last_valid_end = word_end;
            line_len += space_needed + word_len;

            pos = word_end;
            while (pos < len && text[pos] == ' ') pos++;
        }

        // If we reached the end of the text, we need to handle the last word
        if (is_last_line && pos < len) {
            const char* ellipsis = "...";
            int dots_len = strlen(ellipsis);

            // If the last word doesn't fit, we need to truncate it
            while (last_valid_end > word_start && (last_valid_end - word_start + dots_len) > width) {
                last_valid_end--;
                while (last_valid_end > word_start && text[last_valid_end - 1] == ' ') {
                    last_valid_end--;
                }
            }

            for (int t = 0; t < tabulation; ++t) cout << '\t';

            for (int i = word_start; i < last_valid_end; ++i)
                cout << text[i];

            cout << ellipsis << endl;
            return;
        }

        for (int t = 0; t < tabulation; ++t) cout << '\t'; // Print tabulation spaces

        for (int i = word_start; i < last_valid_end; ++i) // Print the line
            cout << text[i];
        cout << endl;

        line_count++;
    }
}

char* Return_name_from_id(ArrayUsers& au, int id) {
    for (int i = 0; i < au.CountUs; i++) {
        if (au.ptrUs[i]->id == id) {
            return au.ptrUs[i]->username;
        }
    }
    return nullptr; // Return nullptr if no user found with the given ID
}

void Delete_message(ArrayUsers& au, User& user, int index) {
    if (index < 0 || index >= user.Count_of_ptrMs) {
        cout << "Invalid message index." << endl;
        return;
    }

    // Optionally, you can resize the array if needed
    if (user.Count_of_ptrMs < user.Size_of_ptrMs - user.Block_of_ptrMs) {
        Message** new_ptr = new Message*[user.Size_of_ptrMs - user.Block_of_ptrMs];
        for (int i = 0; i < user.Count_of_ptrMs; i++) {
            new_ptr[i] = user.ptrMs[i];
        }
        delete[] user.ptrMs; // Free old array
        user.ptrMs = new_ptr; // Point to the new array
        user.Size_of_ptrMs -= user.Block_of_ptrMs; // Decrease size
    }

    // Shift messages to the left to remove the message at index
    for (int i = index; i < user.Count_of_ptrMs - 1; i++) {
        user.ptrMs[i] = user.ptrMs[i + 1];
    }
    user.Count_of_ptrMs--; // Decrease the count of messages

    cout << "Message deleted successfully." << endl;
}

void Delete_message(ArrayUsers& au, int index) {
    if (index < 0 || index >= au.CountMs) {
        cout << "Invalid message index." << endl;
        return;
    }

    // Optionally, you can resize the array if needed
    if (au.CountMs < au.SizeMs - au.Block) {
        Message** new_ptr = new Message*[au.SizeMs - au.Block];
        for (int i = 0; i < au.CountMs; i++) {
            new_ptr[i] = au.ptrMs[i];
        }
        delete[] au.ptrMs; // Free old array
        au.ptrMs = new_ptr; // Point to the new array
        au.SizeMs -= au.Block; // Decrease size
    }

    // Shift messages to the left to remove the message at index
    for (int i = index; i < au.CountMs - 1; i++) {
        au.ptrMs[i] = au.ptrMs[i + 1];
    }
    au.CountMs--; // Decrease the count of messages
}

void Publish_message(ArrayUsers au, int pos) {
    char menu[3][50] = {
        "1. Send to specific user",
        "2. Make a post",
        "3. Come back"
    };

    bool end = false;
    while (!end) {
        system("cls");
        Menu(menu, 3);
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                system("cls");
                char username[50];
                cout << "Enter username to send message: ";
                cin.ignore();
                cin.getline(username, 50);
                int user_pos = Get_position_of_user(au, username);
                if (user_pos == -1) {
                    cout << "User not found.\n(if you dont remember username, you can go to past menu, and choose \"Find user\".)" << endl;
                    system("pause");
                    continue;
                }
                // Send message logic here
                break;
            }
            case 2:
                // Post logic here
                break;
            case 3:
                end = true; // Exit the loop
                break;
            default:
                system("cls");
                cout << "error #6" << endl;
                cout << "Invalid choice. Please try again." << endl;
                system("pause");
        }
    }
}

// Helper function to print a single message (common for posts and personal messages)
void Print_single_message(ArrayUsers& au, Message* msg, bool show_to = false) {
    cout << "From: " << Return_name_from_id(au, msg->from_id);
    if (show_to) {
        cout << ", To: " << Return_name_from_id(au, msg->to_id);
    }
    cout << ".\tMessage: ";
    Print_wrap_text(msg->message, 35, 1, 4);
    cout << "\tDate: " << msg->date << ", Time: " << msg->time << endl;
}

// Generalized function to print messages with pagination and selection
void Print_messages(ArrayUsers& au, Message** messages, int count, bool show_to = false, bool allow_delete = false) {
    if (count == 0) {
        cout << "No messages found." << endl;
        system("pause");
        return;
    }

    int per_page = 5;
    int pages = (count + per_page - 1) / per_page;
    int current_page = 1;

    while (true) {
        system("cls");
        cout << "Messages List. Page " << current_page << " of " << pages << "." << endl << endl;
        int start = (current_page - 1) * per_page;
        int end = min(start + per_page, count);
        for (int i = start; i < end; i++) {
            Print_single_message(au, messages[i], show_to);
        }
        cout << endl;
        cout << "Total messages: " << count << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Next page" << endl;
        cout << "2. Previous page" << endl;
        cout << "3. Choose message (1-" << (end - start) << ")" << endl;
        cout << "4. Exit" << endl;
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                if (current_page < pages) {
                    current_page++;
                } else {
                    cout << "You are already on the last page." << endl;
                    system("pause");
                }
                break;
            case 2:
                if (current_page > 1) {
                    current_page--;
                } else {
                    cout << "You are already on the first page." << endl;
                    system("pause");
                }
                break;
            case 3: {
                system("cls");
                int msg_choice;
                cout << "Choose a message (1-" << (end - start) << "): ";
                cin >> msg_choice;
                if (msg_choice < 1 || msg_choice > (end - start)) {
                    system("cls");
                    cout << "error #6" << endl;
                    cout << "Invalid choice. Please try again." << endl;
                    system("pause");
                } else {
                    int index = start + msg_choice - 1;
                    Print_single_message(au, messages[index], show_to);
                    cout << endl;
                    // Handle message type logic
                    if (messages[index]->type == POST) {
                        if (allow_delete) {
                            cout << "Here some errors..." << endl;
                            Delete_message(au, index);
                        }
                        system("pause");
                        continue;
                    } else if (messages[index]->type == TEXT) {
                        cout << "Respond? (y/n):" << endl;
                        // Add response logic if needed
                    } else if (messages[index]->type == ADMIN_ACCESS || messages[index]->type == CREATOR_ACCESS) {
                        cout << "Accept? (y/n):" << endl;
                        // Add accept logic if needed
                    }
                    system("pause");
                }
                break;
            }
            case 4:
                return; // Exit the message list
            default:
                system("cls");
                cout << "error #6" << endl;
                cout << "Invalid choice. Please try again." << endl;
                system("pause");
        }
    }
}

void Print_posts(ArrayUsers au) {
    Load_posts_data(au);
    Print_messages(au, au.ptrMs, au.CountMs, false, true);
}

void Personal_messages(ArrayUsers au, User user) {
    Print_messages(au, user.ptrMs, user.Count_of_ptrMs, true, false);
}

void View_user_posts(ArrayUsers au, int pos) {
    if (au.ptrUs[pos]->Count_of_ptrMs == 0) {
        cout << "No posts found." << endl;
        return;
    }

    Print_messages(au, au.ptrUs[pos]->ptrMs, au.ptrUs[pos]->Count_of_ptrMs, false, true);
    system("cls");
    return; // Return to the previous menu
}

void View_user_posts_Main(ArrayUsers au) {
    int pos = 0;
    char username[50];
    
    char menu[4][50] = {
        "1. Find user by ID",
        "2. Find user by Name",
        "3. Print all user posts",
        "4. Come back"
    };
    bool end = false;
    while (!end) {
        system("cls");
        Menu(menu, 4);
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                system("cls");
                cout << "Enter user ID: ";
                cin >> pos;
                pos = Get_position_of_user(au, pos);
                if (pos == -1) {
                    cout << "User not found." << endl;
                    system("pause");
                    continue;
                } else {
                    cout << "User found: " << au.ptrUs[pos]->username << endl;
                    system("pause");
                }
                break;
            case 2:
                system("cls");
                Search(au.ptrUs, au.CountUs);
                break;
            case 3:
                system("cls");
                if (au.CountUs == 0) {
                    cout << "No users found." << endl;
                    system("pause");
                    continue;
                }
                cout << "Enter user Name to view posts: ";
                cin.ignore();
                cin.getline(username, 50);
                pos = Get_position_of_user(au, username);
                if (pos == -1) {
                    cout << "User not found." << endl;
                    system("pause");
                    continue;
                }
                View_user_posts(au, pos);
                break;
            case 4:
                end = true; // Exit the loop
                break;
            default:
                system("cls");
                cout << "error #6" << endl;
                cout << "Invalid choice. Please try again." << endl;
                system("pause");
                break;
        }
    }
}

void Print_Masseges_main(ArrayUsers au, int my_pos) {
    int page = 1;

    char menu[4][50] = {
        "1. Personal messages",
        "2. Posts",
        "3. View user posts",
        "4. Come back"
    };

    bool end = false;
    while (!end) {
        system("cls");
        Menu(menu, 4);
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                system("cls");
                Personal_messages(au, *au.ptrUs[my_pos]);
                break;
            case 2:
                system("cls");
                Print_posts(au);
                break;
            case 3:
                system("cls");
                View_user_posts_Main(au);
                break;
            case 4:
                system("cls");
                end = true;
                break;
            default:
                system("cls");
                cout << "error #6" << endl;
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void Messanger(ArrayUsers& au, int id) {
    int pos = Get_position_of_user(au, id);

    char menu[4][50] = {
        "1. All messages",
        "2. Send message",
        "3. Find user",
        "4. Come back"
    };

    bool end = false;
    while (!end) {
        system("cls");
        Menu(menu, 4);

        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            Print_Masseges_main(au, pos);
            break;
        case 2:
            system("cls");
            system("pause");
            break;
        case 3:
            system("cls");
            Search(au.ptrUs, au.CountUs);
            break;
        case 4:
            system("cls");
            end = true;
            break;
        default:
            break;
        }
    }
    return;
}
