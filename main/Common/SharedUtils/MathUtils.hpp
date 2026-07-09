class MathUtils
{
    public:
        static int Wrap(int index, int max_value) 
        {
            return (index % max_value + max_value) % max_value;
        }

        template<typename TEnum>
        static TEnum WrapEnum(TEnum value, int delta, int count)
        {
            int v = static_cast<int>(value);
            v = (v + delta + count) % count;
            return static_cast<TEnum>(v);
        }

};