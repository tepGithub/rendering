namespace Math
{
    template <class T>
    struct color3
    {
		union
		{
			T m_data[3];
			struct { T r, g, b; };
		};
        
		// Constructors
		color3() {}
		constexpr color3(T _r) : m_data{ _r, _r, _r } {}
		constexpr color3(T _r, T _g, T _b) : m_data{ _r, _g, _b } {}
		constexpr color3(const color3& other) : m_data{ other[0], other[1], other[2] } {}
		constexpr color3(const T(&other)[3]) : m_data{ other[0], other[1], other[2] } {}

		// Array operators
		constexpr T&        operator[] (unsigned int i) { return m_data[i]; }
		constexpr const T&  operator[] (unsigned int i) const { return m_data[i]; }
		constexpr T*        begin() { return m_data; }
		constexpr const T*  begin() const { return m_data; }
		constexpr T*        end() { return (m_data + 3); }
		constexpr const T*  end() const { return (m_data + 3); }
    };

    template <class T>
    struct color4
    {
		union
		{
			T m_data[4];
			struct { T r, g, b, a; };
		};

 		// Constructors
		color4() {}
		constexpr color4(T _r) : m_data{ _r, _r, _r, _r } {}
		constexpr color4(T _r, T _g, T _b, T _a=255) : m_data{ _r, _g, _b, _a } {}
		constexpr color4(const color4& other) : m_data{ other[0], other[1], other[2], other[3] } {}
		constexpr color4(const T(&other)[4]) : m_data{ other[0], other[1], other[2], other[3] } {}

		// Array operators
		constexpr T&        operator[] (unsigned int i) { return m_data[i]; }
		constexpr const T&  operator[] (unsigned int i) const { return m_data[i]; }
		constexpr T*        begin() { return m_data; }
		constexpr const T*  begin() const { return m_data; }
		constexpr T*        end() { return (m_data + 4); }
		constexpr const T*  end() const { return (m_data + 4); }
    };

    using color3f = color3<float>;
    using color4f = color4<float>;
    using color3b = color3<unsigned char>;
    using color4b = color4<unsigned char>;

    struct colors
    {
        static color3b black() { return color3b(0, 0, 0); }
        static color3b white() { return color3b(255, 255, 255); }
    };
}