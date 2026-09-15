#include <iostream>
using namespace std;

class Song
{
public:
    int songID{};
    string title{};
    string artist{};
    int duration{};
};

class MusicPlayer
{
private:
    class SongNode
    {
    public:
        Song song;
        SongNode *next;
        SongNode *prev;

        SongNode(const Song &s = Song())
            : song(s), next(nullptr), prev(nullptr) {}
    };

    SongNode *Head;
    SongNode *Tail;
    SongNode *currentSong;
    int songCount;

public:
    MusicPlayer() : Head(nullptr), Tail(nullptr), currentSong(nullptr), songCount(0) {}
    ~MusicPlayer()
    {
        clear();
    }

    void addSongAtHead(const Song &s)
    {
        auto newNode = new SongNode(s);

        if (Head == nullptr || Tail == nullptr)
        {
            Head = newNode;
            Tail = newNode;
            Head->prev = Tail;
            Tail->next = Head;
            Tail->prev = Head;
            Head->next = Tail;

            currentSong = Head;
            songCount++;

            return;
        }

        newNode->next = Head;
        newNode->prev = Tail;
        Tail->next = newNode;
        Head->prev = newNode;

        Head = newNode;
        songCount++;
    }
    void addSongAtTail(const Song &s)
    {
        auto newNode = new SongNode(s);

        if (Head == nullptr || Tail == nullptr)
        {
            Head = newNode;
            Tail = newNode;
            Head->prev = Tail;
            Tail->next = Head;
            Tail->prev = Head;
            Head->next = Tail;
            songCount++;

            return;
        }

        newNode->next = Head;
        newNode->prev = Tail;
        Tail->next = newNode;
        Head->prev = newNode;

        Tail = newNode;
        songCount++;
    }
    void insertSongAtPosition(const Song &s, int pos)
    {
        if (!Head)
        {
            return;
        }

        int zPos = pos - 1;
        int count = 0;
        auto ptr = Head;
        while (count < zPos)
        {
            ptr = ptr->next;
            count++;
        }

        auto newNode = new SongNode(s);
        newNode->next = ptr->next;
        newNode->prev = ptr;
        ptr->next->prev = newNode;
        ptr->next = newNode;

        songCount++;
    }
    bool removeSongByID(int songID)
    {
        if (!Head)
        {
            return true;
        }

        if (Head->next == Head)
        {
            delete Head;
            songCount--;

            Tail = nullptr;
            Head = nullptr;
            currentSong = nullptr;

            return true;
        }

        auto ptr = Head;

        do
        {
            if (ptr->song.songID == songID)
            {
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
                if (ptr == currentSong)
                {
                    currentSong = ptr->next;
                }

                if (ptr == Head)
                {
                    Head = ptr->next;
                }

                if (ptr == Tail)
                {
                    Tail = ptr->prev;
                }

                delete ptr;
                songCount--;
                return true;
            }

            ptr = ptr->next;
        } while (ptr != Head);

        cout << "[ERROR] No song with songID: " << songID << " found.\n";
        return false;
    }

    void playNext()
    {
        currentSong = currentSong->next;
    }
    void playPrevious()
    {
        currentSong = currentSong->prev;
    }

    void displayPlaylistForward() const
    {
        if (!Head)
            return;

        auto ptr = Head;
        do
        {
            cout << ptr->song.songID << "->";
            ptr = ptr->next;
        } while (ptr != Head);
        cout << "->" << "HEAD\n";
    }
    void displayPlaylistBackward() const
    {
        if (!Tail)
            return;

        auto ptr = Tail;
        do
        {
            cout << ptr->song.songID << "->";
            ptr = ptr->prev;
        } while (ptr != Tail);
        cout << "->" << "TAIL\n";
    }

    SongNode *searchSongByID(int songID) const
    {
        auto ptr = Head;

        do
        {
            if (ptr->song.songID == songID)
            {
                return ptr;
            }
            ptr = ptr->next;
        } while (ptr != Head);

        cout << "[ERROR] No song for songID " << songID << " found.\n";
        return nullptr;
    }

    void reversePlaylist()
    {
        if (!Head)
        {
            return;
        }

        if (Head->next == Tail)
        {
            swap(Head, Tail);
            return;
        }

        auto ptr = Head;
        do
        {
            auto temp = ptr->next;
            ptr->next = ptr->prev;
            ptr->prev = temp;

            ptr = temp;
        } while (ptr != Head);

        swap(Head, Tail);
    }

    void removeDuplicates()
    {
        if (!Head)
        {
            return;
        }

        auto ptr = Head;
        do
        {
            auto current = ptr->next;
            while (current != ptr)
            {
                if (current->song.songID == ptr->song.songID)
                {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;

                    if (current == currentSong)
                    {
                        currentSong = current->next;
                    }

                    if (current == Head)
                    {
                        Head = current->next;
                    }

                    if (current == Tail)
                    {
                        Tail = current->prev;
                    }

                    auto temp = current;
                    current = current->next;
                    delete temp;
                    songCount--;
                }

                current = current->next;
            }

            ptr = ptr->next;
        } while (ptr != Head);
    }

    void moveSong(int currentPosition, int newPosition)
    {
        if (!Head)
            return;

        if (currentPosition == newPosition)
            return;

        int currentPos = currentPosition - 1;
        int newPos = newPosition - 1;

        auto toMove = Head;
        auto target = Head;
        while (currentPos--)
        {
            toMove = toMove->next;
        }

        while (newPos--)
        {
            target = target->next;
        }

        auto toMovePrev = toMove->prev;
        auto toMoveNext = toMove->next;

        toMovePrev->next = toMoveNext;
        toMoveNext->prev = toMovePrev;

        auto targetPrev = target->prev;
        targetPrev->next = toMove;
        target->prev = toMove;
        toMove->next = target;
        toMove->prev = targetPrev;
    }

    void swapAdjacentSongs()
    {
        if (!Head)
        {
            return;
        }

        if (Head == Head->next)
        {
            return;
        }

        if (Head->next == Tail)
        {
            swap(Head, Tail);
            return;
        }

        auto ptr = Head;
        Head = Head->next;
        do
        {

            auto temp = ptr->next->next;
            auto prev = ptr->prev;
            auto next = ptr->next;

            ptr->next = temp;
            ptr->prev = next;
            temp->prev = ptr;

            next->next = ptr;
            next->prev = prev;
            prev->next = next;

            ptr = temp;
        } while (ptr != Head && ptr->next != Head);

        Tail = Head->prev;
    }

    int getSongCount() const
    {
        return songCount;
    }
    bool isEmpty() const
    {
        return songCount == 0;
    }
    void clear()
    {
        if (!Head)
            return;

        if (Head->next == Head)
        {
            delete Head;
            Head = nullptr;
            return;
        }

        auto ptr = Head->next;
        while (ptr != Head)
        {
            auto temp = ptr->next;
            delete ptr;
            ptr = temp;
        }

        delete ptr;
    }
};

int main()
{
    cout << "Hello World!\n";
}
