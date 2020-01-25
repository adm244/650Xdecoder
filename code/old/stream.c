#ifndef _STREAM_C_
#define _STREAM_C_

typedef struct {
  void *p;
  size_t size;
} buffer_t;

typedef struct {
  buffer_t buffer;
  size_t pos;
} stream_t;

internal void stream_init(stream_t *stream, void *buffer, size_t size)
{
  assert(stream);
  assert(buffer);
  
  stream->buffer.p = buffer;
  stream->buffer.size = size;
  stream->pos = 0;
}

internal bool stream_eof(stream_t *stream)
{
  assert(stream);
  assert(stream->buffer.p);
  
  return (stream->pos >= stream->buffer.size);
}

internal byte stream_read_byte(stream_t *stream)
{
  assert(stream);
  assert(stream->buffer.p);
  
  //TODO(adm244): error handling
  {
    byte *p = (byte *)stream->buffer.p;
    return p[stream->pos++];
  }
}

internal word stream_read_word(stream_t *stream)
{
  assert(stream);
  assert(stream->buffer.p);
  
  //TODO(adm244): error handling
  {
    byte bl = stream_read_byte(stream);
    byte bh = stream_read_byte(stream);
    
    return (word)((bh << 8) | bl);
  }
}

#endif
