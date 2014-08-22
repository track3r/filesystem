#import <FileHandle.h>


static void finalizer(value abstract_object)
{ 
     FileHandle* np = (FileHandle *)val_data(abstract_object);
     delete np;
} 

DEFINE_KIND(k_FileHandle);
value FileHandle::createHaxePointer()
{
	value v;
	v = alloc_abstract(k_FileHandle, new FileHandle());
	val_gc(v, (hxFinalizer) &finalizer);
	return v;
}

void FileHandle::close()
{
	if(fileHandle)
	{
        fflush(fileHandle);
        fclose(fileHandle);
    }

    if(staticFile)
    {
    	AAsset_close(staticFile);
    }

	fileHandle = 0;
	staticFile = 0;
}

FileHandle::~FileHandle()
{
	close();
}
