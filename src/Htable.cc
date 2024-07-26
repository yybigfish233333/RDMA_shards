#include <htable.hh>

namespace HtableRDMA
{
    int main()
    {
        // 获取Singleton实例并调用其方法
        Htable &instance = Htable::getInstance();
        instance.showTable();

        // 试图获取第二次实例，实际上是同一个实例
        Htable &instance2 = Htable::getInstance();
        instance2.showTable();
        return 0;
    }
}
