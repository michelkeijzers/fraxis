class MathUtils
{
    public:
        static int32_t Wrap(uint32_t index, uint32_t max_value) 
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