// =====================================================================================
// EdgeDetails.h
// =====================================================================================

namespace EdgeDetailsEmpty {

    // just for testing 
    class EmptyEdgeDetails {

    public:
        // c'tors
        EmptyEdgeDetails() = default;
    };
}

namespace EdgeDetailsTest {

    class TestEdgeDetails {
    private:
        std::string m_text;

    public:
        // c'tors
        TestEdgeDetails() : m_text(std::string("")) {}
        TestEdgeDetails(std::string text) : m_text(text) {}

        // getter
        std::string getText() const { return m_text; };
    };

    std::ostream& operator << (std::ostream& os, const TestEdgeDetails& details) {
        os << details.getText();
        return os;
    }
}

namespace EdgeDetailsCities {

    class RouteDetails {
    private:
        std::string m_route;

    public:
        // c'tors
        RouteDetails() : m_route(std::string("")) {}
        RouteDetails(std::string route) : m_route(route) {}

        // getter
        std::string getRoute() const { return m_route; };
    };

    std::ostream& operator << (std::ostream& os, const RouteDetails& details) {
        os << details.getRoute();
        return os;
    }
}

namespace EdgeDetailsFlightInfo {

    class FlightEdgeInfo {
    public:
        FlightEdgeInfo() = default;
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
