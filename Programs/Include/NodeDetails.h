// =====================================================================================
// NodeDetails.h
// =====================================================================================

namespace NodeDetailsEmpty {

    // just for testing 
    class EmptyNodeDetails {

    public:
        // c'tors
        EmptyNodeDetails() = default;
    };
}

namespace NodeDetailsNumbered {

    class NumberedNodeDetails {
    private:
        int m_number;
    public:
        // c'tors
        NumberedNodeDetails() : m_number(0) {}
        NumberedNodeDetails(int number) : m_number(number) {}

        // getter
        int getNumber() const { return m_number; };
    };
}

namespace NodeDetailsTest {

    class TestNodeDetails {

        friend std::ostream& operator << (std::ostream&, const TestNodeDetails&);
    
    private:
        int m_number;
        std::string m_text;

    public:
        // c'tors
        TestNodeDetails() : m_number{ 0 }, m_text(std::string{ "" }) {}
        TestNodeDetails(int number, std::string text) : m_number{ number }, m_text{ text } {}

        // getter
        int getNumber() const { return m_number; };
        std::string getText() const { return m_text; };
    };

    std::ostream& operator << (std::ostream& os, const TestNodeDetails& details) {
        os << "[" << details.m_number << "] " << details.m_text;
        return os;
    }
}

namespace NodeDetailsCities {

    class CityDetails {
    private:
        int m_number;
        std::string m_name;
        std::string m_mapId;

    public:
        // c'tors
        CityDetails() : m_number(0), m_name(std::string("")), m_mapId(std::string("")) {}
        CityDetails(int number, std::string name, std::string mapId) : m_number(number), m_name(name), m_mapId(mapId) {}

        // getter
        int getNumber() const { return m_number; };
        std::string getName() const { return m_name; };
        std::string getMapId() const { return m_mapId; };
    };

    std::ostream& operator << (std::ostream& os, const CityDetails& details) {
        os << "[" << details.getMapId() << "] " << details.getName();
        return os;
    }
}

namespace NodeDetailsFlightInfo {

    class FlightNodeInfo {
    private:
        std::string m_departure;
    public:
        // c'tors
        FlightNodeInfo() = default;
        FlightNodeInfo(std::string departure) : m_departure(departure) {}

        // getter
        std::string getDeparture() const { return m_departure; };
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
